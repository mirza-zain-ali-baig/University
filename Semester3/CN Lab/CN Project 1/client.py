import socket
import threading
import tkinter as tk
from tkinter import *
from tkinter import messagebox, filedialog, simpledialog
import cv2, pickle, os, time, io
from datetime import datetime
from PIL import Image, ImageTk
import pyaudio
import queue


# ═══════════════════════════════════════════════
#  COLOUR PALETTE  — deep dark teal / WhatsApp-ish
# ═══════════════════════════════════════════════
BG_ROOT      = "#0a0f14"
BG_SIDEBAR   = "#111920"
BG_ITEM      = "#111920"
BG_ITEM_HOV  = "#1a2530"
BG_ITEM_SEL  = "#1e2d3a"
BG_CHAT      = "#0d1821"
BG_HEADER    = "#111920"
BG_INPUT     = "#182230"
BG_ME        = "#00523a"
BG_THEM      = "#1e2d3a"
BG_SYS       = "#1a2a1a"
ACCENT       = "#00d97e"
ACCENT2      = "#00a86b"
RED          = "#e5484d"
BORDER       = "#1e2d3a"
TXT_PRI      = "#e8edf2"
TXT_SEC      = "#7a9ab0"
TXT_MUTED    = "#4a6070"
WHITE        = "#ffffff"
ONLINE_DOT   = "#00d97e"
UNREAD_BG    = "#00d97e"
UNREAD_FG    = "#0a0f14"


class RoundedCanvas(tk.Canvas):
    """A canvas that draws a rounded-rectangle background."""
    def __init__(self, parent, radius=12, fill=BG_ME, **kw):
        super().__init__(parent, highlightthickness=0, bd=0,
                         bg=parent.cget("bg"), **kw)
        self._fill   = fill
        self._radius = radius
        self.bind("<Configure>", self._redraw)

    def _redraw(self, _=None):
        self.delete("bg")
        w, h = self.winfo_width(), self.winfo_height()
        r = self._radius
        self.create_arc(0, 0, 2*r, 2*r,   start=90,  extent=90,  fill=self._fill, outline=self._fill, tags="bg")
        self.create_arc(w-2*r, 0, w, 2*r, start=0,   extent=90,  fill=self._fill, outline=self._fill, tags="bg")
        self.create_arc(0, h-2*r, 2*r, h, start=180, extent=90,  fill=self._fill, outline=self._fill, tags="bg")
        self.create_arc(w-2*r, h-2*r, w, h, start=270, extent=90, fill=self._fill, outline=self._fill, tags="bg")
        self.create_rectangle(r, 0, w-r, h,   fill=self._fill, outline=self._fill, tags="bg")
        self.create_rectangle(0, r, w,   h-r, fill=self._fill, outline=self._fill, tags="bg")
        self.tag_lower("bg")


def _avatar_canvas(parent, text, size=42, bg_fill=ACCENT2, parent_bg=BG_SIDEBAR):
    c = tk.Canvas(parent, width=size, height=size,
                  bg=parent_bg, highlightthickness=0)
    pad = 2
    c.create_oval(pad, pad, size-pad, size-pad, fill=bg_fill, outline="")
    c.create_text(size//2, size//2, text=text[:2].upper(),
                  font=("Trebuchet MS", size//4, "bold"), fill=WHITE)
    return c


class ScrollableFrame(tk.Frame):
    """A vertically-scrollable frame."""
    def __init__(self, parent, bg=BG_SIDEBAR, **kw):
        super().__init__(parent, bg=bg, **kw)
        self.canvas = tk.Canvas(self, bg=bg, highlightthickness=0, bd=0)
        self.scrollbar = tk.Scrollbar(self, orient=VERTICAL,
                                      command=self.canvas.yview,
                                      bg=bg, troughcolor=bg,
                                      width=4)
        self.inner = tk.Frame(self.canvas, bg=bg)
        self.inner.bind("<Configure>",
            lambda e: self.canvas.configure(
                scrollregion=self.canvas.bbox("all")))
        self._win = self.canvas.create_window((0,0), window=self.inner, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)
        self.canvas.pack(side=LEFT, fill=BOTH, expand=True)
        self.scrollbar.pack(side=RIGHT, fill=Y)
        self.canvas.bind("<Configure>",
            lambda e: self.canvas.itemconfig(self._win, width=e.width))
        self.canvas.bind_all("<MouseWheel>",
            lambda e: self.canvas.yview_scroll(-1*(e.delta//120), "units"))

    def scroll_bottom(self):
        self.canvas.yview_moveto(1.0)


class ChatClient:
    def __init__(self, root):
        self.root = root
        self.root.title("WhatsApp Pro Max")
        self.root.geometry("1100x680")
        self.root.configure(bg=BG_ROOT)
        self.root.minsize(800, 560)

        # ── Login ──
        self.username = simpledialog.askstring(
            "Login", "Enter your username:", parent=root)
        if not self.username:
            root.destroy()
            return

        # ── Connect (UNCHANGED) ──
        self.client = socket.socket()
        self.client.connect(('127.0.0.1', 5555))
        self.client.send(f"{self.username}\n".encode())

        # ── State (UNCHANGED) ──
        self.chats        = {}
        self.current_chat = None
        self.unread       = {}
        self.is_calling   = False
        self.call_active  = False
        self.call_partner = None
        self.call_type    = None

        # ── Media (UNCHANGED) ──
        self.media_queue  = queue.Queue()
        self.partner_frame = None
        self.partner_photo = None
        self.partner_label = None
        self.local_label   = None
        self._stop_video   = threading.Event()

        # ── UI ──
        self._chat_item_widgets = {}   # name -> item_frame
        self._chat_item_badge   = {}   # name -> badge_label
        self._chat_item_preview = {}   # name -> preview_label
        self.setup_ui()

        # ── Threads (UNCHANGED) ──
        threading.Thread(target=self.receive,       daemon=True).start()
        threading.Thread(target=self.media_handler, daemon=True).start()
        self.root.after(50, self.update_partner_video)

    # ════════════════════════════════════════════
    #  MEDIA HANDLER  (UNCHANGED)
    # ════════════════════════════════════════════
    def media_handler(self):
        p = None
        stream = None
        while True:
            try:
                item = self.media_queue.get()
                if item is None:
                    break
                header, data = item
                if header.startswith("VIDEO"):
                    frame = pickle.loads(data)
                    img = cv2.imdecode(frame, cv2.IMREAD_COLOR)
                    if img is not None:
                        img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
                        pil_img = Image.fromarray(img_rgb)
                        pil_img = pil_img.resize((260, 195))
                        self.partner_frame = pil_img
                elif header.startswith("VOICE"):
                    if p is None:
                        p = pyaudio.PyAudio()
                        stream = p.open(format=pyaudio.paInt16, channels=1,
                                        rate=44100, output=True,
                                        frames_per_buffer=1024)
                    stream.write(data)
                elif header.startswith("VIDCALL_END"):
                    self.partner_frame = None
                    if stream:
                        stream.stop_stream(); stream.close()
                    if p:
                        p.terminate()
                    stream = p = None
            except Exception:
                break

    def update_partner_video(self):
        if self.partner_frame is not None:
            self.partner_photo = ImageTk.PhotoImage(self.partner_frame)
            if self.partner_label is None:
                self.partner_label = tk.Label(self.msg_inner,
                                              bg=BG_CHAT,
                                              relief=FLAT)
                self.partner_label.pack(anchor="w", pady=4, padx=14)
            self.partner_label.config(image=self.partner_photo)
        else:
            if self.partner_label:
                self.partner_label.config(image="")
        self.root.after(50, self.update_partner_video)

    # ════════════════════════════════════════════
    #  UI SETUP
    # ════════════════════════════════════════════
    def setup_ui(self):
        self.root.columnconfigure(0, weight=0)
        self.root.columnconfigure(1, weight=1)
        self.root.rowconfigure(0, weight=1)

        self._build_sidebar()
        self._build_chat_panel()

    # ─── SIDEBAR ───────────────────────────────
    def _build_sidebar(self):
        sidebar = tk.Frame(self.root, bg=BG_SIDEBAR, width=290)
        sidebar.grid(row=0, column=0, sticky="nsew")
        sidebar.grid_propagate(False)

        # Header
        hdr = tk.Frame(sidebar, bg=BG_HEADER, height=62)
        hdr.pack(fill=X)
        hdr.pack_propagate(False)

        av = _avatar_canvas(hdr, self.username, size=38,
                            bg_fill=ACCENT2, parent_bg=BG_HEADER)
        av.pack(side=LEFT, padx=(14,8), pady=12)

        name_fr = tk.Frame(hdr, bg=BG_HEADER)
        name_fr.pack(side=LEFT, fill=Y, pady=12)
        tk.Label(name_fr, text=self.username,
                 font=("Trebuchet MS", 13, "bold"),
                 bg=BG_HEADER, fg=TXT_PRI).pack(anchor="w")
        tk.Label(name_fr, text="● online",
                 font=("Trebuchet MS", 9),
                 bg=BG_HEADER, fg=ACCENT).pack(anchor="w")

        # Divider
        tk.Frame(sidebar, bg=BORDER, height=1).pack(fill=X)

        # Search
        s_fr = tk.Frame(sidebar, bg=BG_SIDEBAR, pady=8, padx=10)
        s_fr.pack(fill=X)
        s_wrap = tk.Frame(s_fr, bg=BG_ITEM_HOV,
                          highlightbackground=BORDER,
                          highlightthickness=1)
        s_wrap.pack(fill=X)
        tk.Label(s_wrap, text="⌕", font=("Trebuchet MS", 13),
                 bg=BG_ITEM_HOV, fg=TXT_MUTED).pack(side=LEFT, padx=(8,2))
        self.search_var = tk.StringVar()
        self.search_var.trace_add("write", lambda *_: self._filter_chats())
        se = tk.Entry(s_wrap, textvariable=self.search_var,
                      font=("Trebuchet MS", 11), bg=BG_ITEM_HOV,
                      fg=TXT_PRI, insertbackground=TXT_PRI,
                      relief=FLAT, bd=0)
        se.pack(side=LEFT, fill=X, expand=True, ipady=6, padx=(0,8))
        se.insert(0, "Search chats…")
        se.bind("<FocusIn>",  lambda e: se.delete(0, END) if se.get()=="Search chats…" else None)
        se.bind("<FocusOut>", lambda e: se.insert(0,"Search chats…") if not se.get() else None)

        # Room buttons row
        rb = tk.Frame(sidebar, bg=BG_SIDEBAR)
        rb.pack(fill=X, padx=10, pady=(0,6))
        for txt, cmd in [("＋ Room", self.create_room),
                         ("→ Join",  self.join_room),
                         ("← Leave", self.leave_room)]:
            b = tk.Button(rb, text=txt,
                          font=("Trebuchet MS", 8, "bold"),
                          bg=BG_ITEM_HOV, fg=TXT_SEC,
                          relief=FLAT, cursor="hand2",
                          activebackground=BORDER,
                          activeforeground=ACCENT,
                          command=cmd, padx=6, pady=3)
            b.pack(side=LEFT, padx=(0,4))

        tk.Frame(sidebar, bg=BORDER, height=1).pack(fill=X)

        # Chat list
        self.chat_scroll = ScrollableFrame(sidebar, bg=BG_SIDEBAR)
        self.chat_scroll.pack(fill=BOTH, expand=True)
        self.chat_list_inner = self.chat_scroll.inner

        # We keep a hidden Listbox for compatibility with old receive() code
        # that calls self.chat_list.get / insert / delete
        self.chat_list = tk.Listbox(sidebar)   # hidden — never packed

    # ─── CHAT PANEL ────────────────────────────
    def _build_chat_panel(self):
        panel = tk.Frame(self.root, bg=BG_CHAT)
        panel.grid(row=0, column=1, sticky="nsew")
        panel.rowconfigure(1, weight=1)
        panel.columnconfigure(0, weight=1)

        # ── Chat header ──
        self.chat_header = tk.Frame(panel, bg=BG_HEADER, height=62)
        self.chat_header.grid(row=0, column=0, sticky="ew")
        self.chat_header.grid_propagate(False)

        self._hdr_av_canvas = _avatar_canvas(self.chat_header, "?",
                                             size=38, bg_fill=TXT_MUTED,
                                             parent_bg=BG_HEADER)
        self._hdr_av_canvas.pack(side=LEFT, padx=(16,10), pady=12)

        hdr_txt = tk.Frame(self.chat_header, bg=BG_HEADER)
        hdr_txt.pack(side=LEFT, fill=Y, pady=12)
        self.chat_title = tk.Label(hdr_txt, text="Select a conversation",
                                   font=("Trebuchet MS", 13, "bold"),
                                   bg=BG_HEADER, fg=TXT_PRI)
        self.chat_title.pack(anchor="w")
        self.chat_subtitle = tk.Label(hdr_txt, text="",
                                      font=("Trebuchet MS", 9),
                                      bg=BG_HEADER, fg=TXT_SEC)
        self.chat_subtitle.pack(anchor="w")

        # call buttons in header
        call_fr = tk.Frame(self.chat_header, bg=BG_HEADER)
        call_fr.pack(side=RIGHT, padx=14, pady=12)

        for emoji, cmd in [("📹", self.video_call), ("📞", self.voice_call)]:
            b = tk.Button(call_fr, text=emoji,
                          font=("Segoe UI Emoji", 16),
                          bg=BG_HEADER, fg=TXT_PRI,
                          relief=FLAT, cursor="hand2",
                          activebackground=BG_ITEM_HOV,
                          activeforeground=ACCENT,
                          command=cmd)
            b.pack(side=LEFT, padx=4)

        self.end_call_btn = tk.Button(call_fr, text="⬛ End",
                                      font=("Trebuchet MS", 9, "bold"),
                                      bg=RED, fg=WHITE,
                                      relief=FLAT, cursor="hand2",
                                      activebackground="#c0333a",
                                      activeforeground=WHITE,
                                      command=self.end_call,
                                      state=DISABLED, padx=8, pady=2)
        self.end_call_btn.pack(side=LEFT, padx=(8,0))

        tk.Frame(panel, bg=BORDER, height=1).grid(row=0, column=0,
                                                   sticky="sew")

        # ── Messages area ──
        msg_outer = tk.Frame(panel, bg=BG_CHAT)
        msg_outer.grid(row=1, column=0, sticky="nsew")
        msg_outer.rowconfigure(0, weight=1)
        msg_outer.columnconfigure(0, weight=1)

        self.msg_canvas = tk.Canvas(msg_outer, bg=BG_CHAT,
                                    highlightthickness=0)
        msg_sb = tk.Scrollbar(msg_outer, orient=VERTICAL,
                               command=self.msg_canvas.yview,
                               bg=BG_CHAT, troughcolor=BG_CHAT, width=4)
        self.msg_inner = tk.Frame(self.msg_canvas, bg=BG_CHAT)
        self.msg_inner.bind("<Configure>",
            lambda e: self.msg_canvas.configure(
                scrollregion=self.msg_canvas.bbox("all")))
        self._msg_win = self.msg_canvas.create_window(
            (0,0), window=self.msg_inner, anchor="nw")
        self.msg_canvas.configure(yscrollcommand=msg_sb.set)
        self.msg_canvas.bind("<Configure>",
            lambda e: self.msg_canvas.itemconfig(self._msg_win, width=e.width))
        self.msg_canvas.grid(row=0, column=0, sticky="nsew")
        msg_sb.grid(row=0, column=1, sticky="ns")

        # ── Input bar ──
        inp = tk.Frame(panel, bg=BG_INPUT, pady=10, padx=12)
        inp.grid(row=2, column=0, sticky="ew")

        # Attach file
        att = tk.Button(inp, text="📎",
                        font=("Segoe UI Emoji", 17),
                        bg=BG_INPUT, fg=TXT_SEC,
                        relief=FLAT, cursor="hand2",
                        activebackground=BG_ITEM_HOV,
                        activeforeground=ACCENT,
                        command=self.send_file)
        att.pack(side=LEFT, padx=(0,8))

        # Text entry wrapper
        entry_wrap = tk.Frame(inp, bg=BG_ITEM_HOV,
                              highlightbackground=BORDER,
                              highlightthickness=1)
        entry_wrap.pack(side=LEFT, fill=X, expand=True)
        self.entry = tk.Entry(entry_wrap,
                              font=("Trebuchet MS", 12),
                              bg=BG_ITEM_HOV, fg=TXT_PRI,
                              insertbackground=ACCENT,
                              relief=FLAT, bd=0)
        self.entry.pack(fill=X, expand=True, ipady=8, padx=10)
        self.entry.bind('<Return>', lambda e: self.send())

        # Send button
        send_btn = tk.Button(inp, text="➤",
                             font=("Trebuchet MS", 14, "bold"),
                             bg=ACCENT, fg=BG_ROOT,
                             relief=FLAT, cursor="hand2",
                             activebackground=ACCENT2,
                             activeforeground=WHITE,
                             command=self.send,
                             padx=14, pady=6)
        send_btn.pack(side=LEFT, padx=(8,0))

        # Welcome message
        self._show_welcome()

    def _show_welcome(self):
        for w in self.msg_inner.winfo_children():
            w.destroy()
        tk.Label(self.msg_inner,
                 text="💬\n\nSelect a conversation to start chatting.",
                 font=("Trebuchet MS", 13),
                 bg=BG_CHAT, fg=TXT_MUTED,
                 justify=CENTER).pack(pady=120)

    # ════════════════════════════════════════════
    #  SIDEBAR CHAT ITEMS
    # ════════════════════════════════════════════
    def _ensure_chat_item(self, name, is_room=False):
        """Create a sidebar item if it doesn't exist."""
        if name in self._chat_item_widgets:
            return

        # Also keep hidden Listbox in sync (old code may reference it)
        existing = list(self.chat_list.get(0, END))
        if name not in existing:
            self.chat_list.insert(END, name)

        item = tk.Frame(self.chat_list_inner, bg=BG_ITEM, cursor="hand2")
        item.pack(fill=X)

        # Subtle bottom border
        tk.Frame(item, bg=BORDER, height=1).pack(side=BOTTOM, fill=X)

        inner = tk.Frame(item, bg=BG_ITEM)
        inner.pack(fill=X, padx=0)

        # Avatar
        av_color = ACCENT2 if not is_room else "#2a5a70"
        av = _avatar_canvas(inner, "🏠" if is_room else name,
                            size=44, bg_fill=av_color,
                            parent_bg=BG_ITEM)
        av.grid(row=0, column=0, rowspan=2, padx=(14,10), pady=10)

        n_lbl = tk.Label(inner, text=name,
                         font=("Trebuchet MS", 12, "bold"),
                         bg=BG_ITEM, fg=TXT_PRI, anchor="w")
        n_lbl.grid(row=0, column=1, sticky="ew", pady=(10,1))

        prev_lbl = tk.Label(inner, text="",
                            font=("Trebuchet MS", 9),
                            bg=BG_ITEM, fg=TXT_SEC, anchor="w")
        prev_lbl.grid(row=1, column=1, sticky="ew", pady=(0,10))

        badge = tk.Label(inner, text="",
                         font=("Trebuchet MS", 8, "bold"),
                         bg=UNREAD_BG, fg=UNREAD_FG,
                         padx=5, pady=1)
        # Don't pack badge yet

        inner.columnconfigure(1, weight=1)

        # Hover / click
        all_wgts = [item, inner, av, n_lbl, prev_lbl]
        def _enter(_=None):
            bg = BG_ITEM_SEL if self.current_chat == name else BG_ITEM_HOV
            for w in all_wgts: w.configure(bg=bg)
            av.configure(bg=bg)
        def _leave(_=None):
            bg = BG_ITEM_SEL if self.current_chat == name else BG_ITEM
            for w in all_wgts: w.configure(bg=bg)
            av.configure(bg=bg)
        def _click(_=None):
            self.open_chat(name)

        for w in all_wgts:
            w.bind("<Enter>",   _enter)
            w.bind("<Leave>",   _leave)
            w.bind("<Button-1>",_click)

        self._chat_item_widgets[name] = (item, inner, av, n_lbl, all_wgts)
        self._chat_item_badge[name]   = badge
        self._chat_item_preview[name] = prev_lbl

    def _set_item_selected(self, name, selected: bool):
        if name not in self._chat_item_widgets:
            return
        item, inner, av, n_lbl, all_wgts = self._chat_item_widgets[name]
        bg = BG_ITEM_SEL if selected else BG_ITEM
        for w in all_wgts:
            w.configure(bg=bg)
        av.configure(bg=bg)

    def _update_preview(self, name, text):
        if name in self._chat_item_preview:
            preview = text[:38] + "…" if len(text) > 38 else text
            self._chat_item_preview[name].config(text=preview)

    def _update_badge(self, name):
        if name not in self._chat_item_badge:
            return
        count = self.unread.get(name, 0)
        badge = self._chat_item_badge[name]
        item, inner, *_ = self._chat_item_widgets[name]
        if count > 0:
            badge.config(text=str(count))
            badge.grid(row=0, column=2, rowspan=2, padx=(4,12))
        else:
            badge.grid_forget()

    def _filter_chats(self):
        q = self.search_var.get().lower()
        for name, (item, *_) in self._chat_item_widgets.items():
            if q in name.lower() or q == "search chats…":
                item.pack(fill=X)
            else:
                item.pack_forget()

    # ════════════════════════════════════════════
    #  OPEN CHAT
    # ════════════════════════════════════════════
    def open_chat(self, name):
        # Strip badge suffix if called from old Listbox paths
        if name.endswith(")"):
            name = name[:name.rfind(" (")]

        prev = self.current_chat
        self.current_chat = name

        # Sidebar highlight
        if prev and prev != name:
            self._set_item_selected(prev, False)
        self._set_item_selected(name, True)

        # Header
        self.chat_title.config(text=name)
        self.chat_subtitle.config(
            text="group room" if name.startswith("Room:") else "● online")
        # Update avatar in header
        self._hdr_av_canvas.delete("all")
        r = 19
        self._hdr_av_canvas.create_oval(2,2,36,36, fill=ACCENT2, outline="")
        self._hdr_av_canvas.create_text(19,19,
            text=name[:2].upper(),
            font=("Trebuchet MS", 10, "bold"), fill=WHITE)

        # Clear unread
        if name in self.unread:
            self.unread[name] = 0
            self._update_badge(name)

        # Clear & reload messages
        for w in self.msg_inner.winfo_children():
            w.destroy()
        self.partner_label = None

        if name in self.chats:
            for msg, sender, is_img in self.chats[name]:
                self.display(msg, sender, is_img)

        self.msg_canvas.update_idletasks()
        self.msg_canvas.yview_moveto(1.0)

    # ─── legacy open_chat used by old Listbox binding ───
    def open_chat_event(self, event):
        sel = self.chat_list.curselection()
        if not sel:
            return
        self.open_chat(self.chat_list.get(sel))

    # ════════════════════════════════════════════
    #  DISPLAY A MESSAGE
    # ════════════════════════════════════════════
    def display(self, msg, sender, is_img=False):
        is_me  = sender == "me"
        is_sys = sender == "system"

        row = tk.Frame(self.msg_inner, bg=BG_CHAT)
        row.pack(fill=X, pady=2, padx=10)

        if is_sys:
            bubble = tk.Frame(row, bg=BG_SYS, padx=12, pady=5)
            bubble.pack(anchor=CENTER)
            tk.Label(bubble, text=msg,
                     font=("Trebuchet MS", 9, "italic"),
                     bg=BG_SYS, fg=ACCENT,
                     wraplength=500).pack()
        elif is_img:
            bubble = tk.Frame(row, bg=BG_ME if is_me else BG_THEM,
                              padx=6, pady=6)
            bubble.pack(anchor="e" if is_me else "w")
            lbl = tk.Label(bubble, image=msg,
                           bg=BG_ME if is_me else BG_THEM)
            lbl.image = msg
            lbl.pack()
            tk.Button(bubble, text="💾 Save",
                      font=("Trebuchet MS", 8),
                      bg=BG_ME if is_me else BG_THEM,
                      fg=ACCENT, relief=FLAT, cursor="hand2",
                      command=lambda m=msg: self.save_chat_image(m)).pack(pady=(3,0))
        elif isinstance(msg, dict) and msg.get('file'):
            bubble = tk.Frame(row, bg=BG_ME if is_me else BG_THEM,
                              padx=12, pady=8)
            bubble.pack(anchor="e" if is_me else "w")
            tk.Label(bubble, text=f"📄  {msg['text']}",
                     font=("Trebuchet MS", 11),
                     bg=BG_ME if is_me else BG_THEM,
                     fg=TXT_PRI, wraplength=340,
                     justify=LEFT).pack(side=LEFT)
            tk.Button(bubble, text="💾",
                      font=("Segoe UI Emoji", 13),
                      bg=BG_ME if is_me else BG_THEM,
                      fg=ACCENT, relief=FLAT, cursor="hand2",
                      command=lambda: self.save_file(
                          msg['name'], msg['data'])).pack(side=LEFT, padx=(8,0))
        else:
            bg  = BG_ME if is_me else BG_THEM
            anc = "e" if is_me else "w"
            bubble = tk.Frame(row, bg=bg, padx=12, pady=7)
            bubble.pack(anchor=anc)
            tk.Label(bubble, text=msg,
                     font=("Trebuchet MS", 11),
                     bg=bg, fg=TXT_PRI,
                     wraplength=420, justify=LEFT).pack()

        self.msg_inner.update_idletasks()
        self.msg_canvas.yview_moveto(1.0)

    def save_file(self, name, data):
        path = filedialog.asksaveasfilename(
            defaultextension="", initialfile=name)
        if path:
            with open(path, "wb") as f:
                f.write(data)

    def save_chat_image(self, photo):
        path = filedialog.asksaveasfilename(
            defaultextension=".png",
            filetypes=[("PNG Image", "*.png")])
        if path:
            img = ImageTk.getimage(photo)
            img.save(path)

    # ════════════════════════════════════════════
    #  ADD MESSAGE
    # ════════════════════════════════════════════
    def add(self, chat, msg, sender, is_img=False):
        if chat not in self.chats:
            self.chats[chat] = []
        self.chats[chat].append((msg, sender, is_img))

        # Update preview text
        preview = msg if isinstance(msg, str) else \
                  (msg.get('text','') if isinstance(msg, dict) else '📷 Image')
        self._update_preview(chat, preview)

        if chat == self.current_chat:
            self.display(msg, sender, is_img)
        else:
            self.unread[chat] = self.unread.get(chat, 0) + 1
            self._update_badge(chat)

    # ════════════════════════════════════════════
    #  SEND  (UNCHANGED LOGIC)
    # ════════════════════════════════════════════
    def send(self):
        msg = self.entry.get()
        if not msg or not self.current_chat:
            messagebox.showwarning("Error", "Select a chat and write a message.")
            return
        time_now = datetime.now().strftime("%H:%M")
        try:
            if self.current_chat.startswith("Room:"):
                room = self.current_chat.replace("Room: ", "")
                self.client.send(f"GROUP|{room}|{msg}\n".encode())
            else:
                self.client.send(f"PRIVATE|{self.current_chat}|{msg}\n".encode())
        except Exception:
            messagebox.showerror("Connection Lost", "Lost connection to server.")
            self.end_call()
            return
        self.add(self.current_chat, f"{msg}  {time_now}", "me")
        self.entry.delete(0, END)

    # ════════════════════════════════════════════
    #  FILE  (UNCHANGED LOGIC)
    # ════════════════════════════════════════════
    def send_file(self):
        path = filedialog.askopenfilename()
        if not path or not self.current_chat:
            return
        size = os.path.getsize(path)
        name = os.path.basename(path)
        if not messagebox.askyesno("Confirm", f"Send  {name}  ({size//1024} KB)?"):
            return
        target = self.current_chat.replace("Room: ", "")
        try:
            with open(path, "rb") as f:
                file_data = f.read()
            header = f"FILE|{target}|{name}|{size}\n"
            self.client.sendall(header.encode() + file_data)
        except Exception:
            messagebox.showerror("Connection Lost", "Lost connection to server.")
            self.end_call()
            return
        chat = self.current_chat
        if name.lower().endswith((".png",".jpg",".jpeg")):
            image = Image.open(path).resize((150,150))
            photo = ImageTk.PhotoImage(image)
            self.add(chat, photo, "me", True)
        else:
            self.add(chat, f"File sent: {name}", "me")
        messagebox.showinfo("Sent", name)

    # ════════════════════════════════════════════
    #  VIDEO CALL  (UNCHANGED LOGIC)
    # ════════════════════════════════════════════
    def video_call(self):
        sel = self.current_chat
        if not sel or self.call_active:
            return
        target = sel.replace("Room: ", "")
        self.call_active  = True
        self.call_partner = target
        self.call_type    = 'video'
        self.end_call_btn.config(state=NORMAL)
        threading.Thread(target=self.send_video_voice,
                         args=(target,), daemon=True).start()
        try:
            self.client.send(f"VIDCALL_REQ|{target}\n".encode())
        except Exception:
            messagebox.showerror("Connection Lost", "Lost connection to server.")
            self.end_call()
            return
        self.add(target, "📹  Video call ringing…", "system")

    def start_video_call(self, target):
        if not self.call_active:
            self.call_active  = True
            self.call_partner = target
            self.call_type    = 'video'
            self.end_call_btn.config(state=NORMAL)
            threading.Thread(target=self.send_video_voice,
                             args=(target,), daemon=True).start()

    def send_video_voice(self, target):
        cap    = cv2.VideoCapture(0)
        p      = pyaudio.PyAudio()
        stream = p.open(format=pyaudio.paInt16, channels=1, rate=44100,
                        input=True, frames_per_buffer=1024)
        try:
            while self.call_active:
                try:
                    ret, frame = cap.read()
                    if not ret:
                        break
                    _, buffer = cv2.imencode('.jpg', frame)
                    data = pickle.dumps(buffer)
                    self.client.sendall(f"VIDEO|{target}|x|{len(data)}\n".encode() + data)
                    audio_data = stream.read(1024, exception_on_overflow=False)
                    self.client.sendall(f"VOICE|{target}|x|{len(audio_data)}\n".encode() + audio_data)
                    def update_local(f=frame):
                        img_rgb = cv2.cvtColor(f, cv2.COLOR_BGR2RGB)
                        pil_img = Image.fromarray(img_rgb).resize((200,200))
                        photo   = ImageTk.PhotoImage(pil_img)
                        if self.local_label and self.local_label.winfo_exists():
                            self.local_label.config(image=photo)
                            self.local_label.image = photo
                    self.root.after(0, update_local)
                except (ConnectionResetError, BrokenPipeError):
                    self.root.after(0, lambda: messagebox.showerror(
                        "Connection Lost", "Lost connection during call."))
                    self.end_call(); break
                except Exception as e:
                    self.root.after(0, lambda: messagebox.showerror(
                        "Error", f"Call error: {e}"))
                    self.end_call(); break
        finally:
            cap.release()
            stream.stop_stream(); stream.close(); p.terminate()
            def clr():
                if self.local_label and self.local_label.winfo_exists():
                    self.local_label.config(image='')
            self.root.after(0, clr)

    def end_call(self, local=True):
        if self.call_active:
            self.call_active = False
            self.end_call_btn.config(state=DISABLED)
            if local and self.call_partner:
                try:
                    self.client.send(f"VIDCALL_END|{self.call_partner}\n".encode())
                except Exception:
                    pass
            def clr():
                if self.local_label and self.local_label.winfo_exists():
                    self.local_label.config(image='')
                if self.partner_label and self.partner_label.winfo_exists():
                    self.partner_label.config(image='')
            self.root.after(0, clr)
            self.add(self.call_partner or "", "📵  Call ended.", "system")
            self.call_partner = self.call_type = None

    # ════════════════════════════════════════════
    #  VOICE CALL  (UNCHANGED LOGIC)
    # ════════════════════════════════════════════
    def voice_call(self):
        sel = self.current_chat
        if not sel or self.call_active:
            return
        target = sel.replace("Room: ", "")
        try:
            self.client.send(f"VIDCALL_REQ|{target}|voice\n".encode())
        except Exception:
            messagebox.showerror("Connection Lost", "Lost connection to server.")
            self.end_call()
            return
        self.add(target, "📞  Voice call ringing…", "system")

    def start_voice_call(self, target):
        if not self.call_active:
            self.call_active  = True
            self.call_partner = target
            self.call_type    = 'voice'
            self.end_call_btn.config(state=NORMAL)
            threading.Thread(target=self.send_voice_only,
                             args=(target,), daemon=True).start()

    def send_voice_only(self, target):
        p      = pyaudio.PyAudio()
        stream = p.open(format=pyaudio.paInt16, channels=1, rate=44100,
                        input=True, frames_per_buffer=1024)
        try:
            while self.call_active:
                try:
                    audio_data = stream.read(1024, exception_on_overflow=False)
                    self.client.sendall(f"VOICE|{target}|x|{len(audio_data)}\n".encode() + audio_data)
                except (ConnectionResetError, BrokenPipeError):
                    self.root.after(0, lambda: messagebox.showerror(
                        "Connection Lost", "Lost connection during call."))
                    self.end_call(); break
                except Exception as e:
                    self.root.after(0, lambda: messagebox.showerror(
                        "Error", f"Call error: {e}"))
                    self.end_call(); break
        finally:
            stream.stop_stream(); stream.close(); p.terminate()

    # ════════════════════════════════════════════
    #  ROOMS  (UNCHANGED LOGIC)
    # ════════════════════════════════════════════
    def create_room(self):
        room = simpledialog.askstring("Create Room", "Room name:", parent=self.root)
        if room:
            try:
                self.client.send(f"CREATE|{room}\n".encode())
            except Exception:
                messagebox.showerror("Connection Lost", "Lost connection to server.")
                return
            rname = "Room: " + room
            self._ensure_chat_item(rname, is_room=True)

    def join_room(self):
        room = simpledialog.askstring("Join Room", "Room name to join:", parent=self.root)
        if room:
            try:
                self.client.send(f"JOIN|{room}\n".encode())
            except Exception:
                messagebox.showerror("Connection Lost", "Lost connection to server.")
                return
            messagebox.showinfo("Joined", room)

    def leave_room(self):
        if not self.current_chat:
            return
        room = self.current_chat.replace("Room: ", "")
        try:
            self.client.send(f"LEAVE|{room}\n".encode())
        except Exception:
            messagebox.showerror("Connection Lost", "Lost connection to server.")
            return
        messagebox.showinfo("Left", room)

    # ════════════════════════════════════════════
    #  UPDATE CHAT LIST (compatibility shim)
    # ════════════════════════════════════════════
    def update_chat_list_display(self):
        """Legacy method — badges now handled by _update_badge."""
        for name in list(self._chat_item_widgets.keys()):
            self._update_badge(name)

    # ════════════════════════════════════════════
    #  RECEIVE  (UNCHANGED LOGIC — only sidebar calls updated)
    # ════════════════════════════════════════════
    def receive(self):
        try:
            import winsound
            HAS_WINSOUND = True
        except ImportError:
            HAS_WINSOUND = False

        while True:
            try:
                raw = self.client.recv(4096)
                try:
                    header = raw.decode()
                except Exception:
                    continue

                # ── USER LIST ──
                if header.startswith("LIST"):
                    users = header.split('|')[1].split(',')
                    # Add new users to sidebar
                    current = set(self._chat_item_widgets.keys())
                    online  = set(u for u in users if u and u != self.username)
                    for u in online:
                        if u not in current:
                            self.root.after(0, lambda n=u: self._ensure_chat_item(n))
                    # Remove offline users
                    for u in current:
                        if not u.startswith("Room:") and u not in online:
                            def _rm(n=u):
                                if n in self._chat_item_widgets:
                                    self._chat_item_widgets[n][0].destroy()
                                    del self._chat_item_widgets[n]
                                    self._chat_item_badge.pop(n, None)
                                    self._chat_item_preview.pop(n, None)
                            self.root.after(0, _rm)

                # ── ROOM LIST ──
                elif header.startswith("ROOMS"):
                    for r in header.split('|')[1].split(','):
                        if r:
                            rname = "Room: " + r
                            self.root.after(0, lambda n=rname:
                                self._ensure_chat_item(n, is_room=True))

                # ── FILE ──
                elif header.startswith("FILE"):
                    parts    = header.split('|', 3)
                    size_str = parts[3]
                    size     = int(''.join(filter(str.isdigit, size_str)))
                    sender, name = parts[1], parts[2]
                    raw_after = size_str[len(str(size)):]
                    data = raw_after.encode()
                    while len(data) < size:
                        data += self.client.recv(min(4096, size - len(data)))
                    chat = sender
                    if name.lower().endswith((".png",".jpg",".jpeg")):
                        image = Image.open(io.BytesIO(data)).resize((150,150))
                        photo = ImageTk.PhotoImage(image)
                        self.root.after(0, lambda p=photo, c=chat:
                            self.add(c, p, "other", True))
                    else:
                        fm = {'file':True,'name':name,'data':data,
                              'text':f"File received: {name}"}
                        self.root.after(0, lambda m=fm, c=chat:
                            self.add(c, m, "other"))

                # ── INCOMING CALL ──
                elif header.startswith("VIDCALL_REQ"):
                    parts     = header.split('|')
                    from_user = parts[1]
                    call_type = 'voice' if len(parts)>2 and parts[2]=='voice' else 'video'
                    if HAS_WINSOUND:
                        def _ring():
                            import winsound
                            for _ in range(3):
                                winsound.Beep(800,200)
                                winsound.Beep(1200,200)
                                time.sleep(0.1)
                        threading.Thread(target=_ring, daemon=True).start()
                    emoji = "📹" if call_type == 'video' else "📞"
                    resp = messagebox.askyesno(
                        "Incoming Call",
                        f"{emoji}  {from_user} is calling you ({call_type}).\nAccept?")
                    if resp:
                        self.client.send(f"VIDCALL_ACC|{from_user}|{call_type}\n".encode())
                        self.add(from_user, f"✅  Accepted {call_type} call.", "system")
                        if call_type == 'video':
                            self.root.after(0, lambda u=from_user:
                                self.start_video_call(u))
                        else:
                            self.root.after(0, lambda u=from_user:
                                self.start_voice_call(u))
                    else:
                        self.client.send(f"VIDCALL_REJ|{from_user}|{call_type}\n".encode())
                        self.add(from_user, f"❌  Rejected {call_type} call.", "system")

                elif header.startswith("VIDCALL_ACC"):
                    parts     = header.split('|')
                    from_user = parts[1]
                    call_type = 'voice' if len(parts)>2 and parts[2]=='voice' else 'video'
                    self.add(from_user, "✅  Call accepted. Connecting…", "system")
                    if call_type == 'video':
                        self.root.after(0, lambda u=from_user:
                            self.start_video_call(u))
                    else:
                        self.root.after(0, lambda u=from_user:
                            self.start_voice_call(u))

                elif header.startswith("VIDCALL_REJ"):
                    parts     = header.split('|')
                    from_user = parts[1]
                    self.add(from_user, "❌  Call rejected.", "system")
                    self.call_active = False
                    self.end_call_btn.config(state=DISABLED)

                elif header.startswith("VIDCALL_END"):
                    self.root.after(0, lambda: self.end_call(local=False))

                elif header.startswith("VIDEO") or header.startswith("VOICE"):
                    size = int(header.split('|')[3])
                    data = b""
                    while len(data) < size:
                        data += self.client.recv(min(4096, size - len(data)))
                    self.media_queue.put((header, data))

                else:
                    time_now = datetime.now().strftime("%H:%M")
                    if header.startswith("[SYSTEM]"):
                        chat = self.current_chat or "System"
                        self.add(chat, f"{header}  {time_now}", "system")
                    elif "[PRIVATE]" in header:
                        sender = header.split()[1].replace(":", "")
                        self.add(sender, f"{header}  {time_now}", "other")
                    else:
                        room = header.split(']')[0][1:]
                        chat = "Room: " + room
                        self.add(chat, f"{header}  {time_now}", "other")

            except Exception as e:
                print("Receive error:", e)
                continue


# ════════════════════════════════════════════════
#  MAIN
# ════════════════════════════════════════════════
root = tk.Tk()
try:
    root.state('zoomed')
except Exception:
    try:
        root.attributes('-zoomed', True)
    except Exception:
        pass
app = ChatClient(root)
root.mainloop()