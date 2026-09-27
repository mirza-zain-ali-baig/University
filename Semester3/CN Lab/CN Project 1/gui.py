import tkinter as tk
from tkinter import scrolledtext, messagebox, simpledialog, filedialog
import os
import threading
import time
from voice_call import VoiceCallManager, CallSignaling as VoiceCallSignaling
from video_call import VideoCallManager, CallSignaling as VideoCallSignaling
from notification import NotificationManager

class ChatGUI:
    def __init__(self, send_callback, connect_callback, file_callback, server_controller=None):
        # Networking and File callbacks
        self.send_callback = send_callback
        self.connect_callback = connect_callback
        self.file_callback = file_callback
        self.server_controller = server_controller
        
        # Initialize call managers
        self.voice_call_manager = VoiceCallManager()
        self.video_call_manager = VideoCallManager()
        
        # Initialize notification manager
        self.notification_manager = NotificationManager()
        
        # Call state tracking
        self.incoming_call_window = None
        self.active_call_window = None
        self.current_call_type = None  # "voice" or "video"
        self.current_caller_name = None  # Store caller name for rejection handling
        self.current_call_target = None  # Store target for rejection handling
        self.call_in_progress = False
        self.call_start_time = None  # Track when call started
        self.call_timer_running = False  # Track if timer is running
        self.call_duration_label = None  # Timer display label
        self.call_timer_thread = None  # Timer update thread
        
        self.win = tk.Tk()
        self.win.title("Real-Time Multi-User Chat")
        self.win.geometry("900x650")

        # --- Screen 1: Login ---
        # Proper screen for login as per rubrics
        self.login_frame = tk.Frame(self.win)
        self.login_frame.pack(pady=50)
        
        # Server Connection Section
        tk.Label(self.login_frame, text="Server Configuration", font=("Arial", 14, "bold")).pack(pady=10)
        
        tk.Label(self.login_frame, text="Server IP Address:", font=("Arial", 11)).pack()
        self.server_ip_entry = tk.Entry(self.login_frame, font=("Arial", 11), width=30)
        self.server_ip_entry.insert(0, "127.0.0.1")
        self.server_ip_entry.pack(pady=5)
        
        tk.Label(self.login_frame, text="Server Port:", font=("Arial", 11)).pack()
        self.server_port_entry = tk.Entry(self.login_frame, font=("Arial", 11), width=30)
        self.server_port_entry.insert(0, "12345")
        self.server_port_entry.pack(pady=5)
        
        # Username Section
        tk.Label(self.login_frame, text="Username", font=("Arial", 14, "bold")).pack(pady=(20, 10))
        
        tk.Label(self.login_frame, text="Username:", font=("Arial", 12)).pack()
        self.name_entry = tk.Entry(self.login_frame, font=("Arial", 12))
        self.name_entry.pack(pady=5)
        
        self.join_btn = tk.Button(self.login_frame, text="Login", command=self.handle_connect, 
                                  bg="#4CAF50", fg="white", width=15)
        self.join_btn.pack(pady=10)

        # --- Screen 2: Main Interface ---
        self.main_frame = tk.Frame(self.win)

        # Top Bar with Call Buttons
        self.top_bar = tk.Frame(self.main_frame, bg="#E0E0E0", height=50)
        self.top_bar.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)
        
        # Current logged-in user shown at top center
        self.user_label = tk.Label(self.top_bar, text="", font=("Arial", 16, "bold"), bg="#E0E0E0")
        self.user_label.place(relx=0.5, rely=0.5, anchor="center")

        # Spacer label
        tk.Label(self.top_bar, text="", bg="#E0E0E0").pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        # Voice Call Button
        self.voice_call_btn = tk.Button(
            self.top_bar,
            text="☎",
            command=self.initiate_voice_call,
            font=("Arial", 14),
            width=4,
            bg="#4CAF50",
            fg="white",
            relief=tk.RAISED
        )
        self.voice_call_btn.pack(side=tk.RIGHT, padx=3, pady=5)
        
        # Video Call Button
        self.video_call_btn = tk.Button(
            self.top_bar,
            text="📹",
            command=self.initiate_video_call,
            font=("Arial", 14),
            width=4,
            bg="#2196F3",
            fg="white",
            relief=tk.RAISED
        )
        self.video_call_btn.pack(side=tk.RIGHT, padx=3, pady=5)

        # Sidebar (Left Side) - Groups & Active Users [cite: 7, 17]
        self.sidebar = tk.Frame(self.main_frame, width=170, bg="#f0f0f0")
        self.sidebar.pack(side=tk.LEFT, fill=tk.Y, padx=5, pady=5)
        
        # Button Frame for Create Group and Options
        self.button_frame = tk.Frame(self.sidebar, bg="#f0f0f0")
        self.button_frame.pack(fill=tk.X, padx=5, pady=5)
        
        # Room Creation Button [cite: 9, 17]
        self.btn_group = tk.Button(self.button_frame, text="+ Create Group", command=self.create_group_popup)
        self.btn_group.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=(0, 2))

        # Three-dot options button (only shown when groups exist and a group is selected)
        self.options_btn = tk.Button(self.button_frame, text="⋮", command=self.on_options_clicked, width=3, state=tk.DISABLED)
        self.options_btn.pack(side=tk.RIGHT, padx=(2, 0))

        self.global_chat_btn = tk.Button(self.sidebar, text="Global Chat", command=self.select_global_chat, bg="#FF9800", fg="white")
        self.global_chat_btn.pack(fill=tk.X, padx=5, pady=(0, 5))

        self.sidebar_canvas = tk.Canvas(self.sidebar, bg="#f0f0f0", highlightthickness=0)
        self.sidebar_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=5)

        self.sidebar_scrollbar = tk.Scrollbar(self.sidebar, orient=tk.VERTICAL, command=self.sidebar_canvas.yview)
        self.sidebar_scrollbar.pack(side=tk.RIGHT, fill=tk.Y, pady=5)
        self.sidebar_canvas.configure(yscrollcommand=self.sidebar_scrollbar.set)

        self.sidebar_inner = tk.Frame(self.sidebar_canvas, bg="#f0f0f0")
        self.sidebar_canvas.create_window((0, 0), window=self.sidebar_inner, anchor="nw")
        self.sidebar_inner.bind("<Configure>", lambda event: self.sidebar_canvas.configure(scrollregion=self.sidebar_canvas.bbox("all")))

        # Chat Area (Right Side)
        self.chat_right = tk.Frame(self.main_frame)
        self.chat_right.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

        self.context_label = tk.Label(self.chat_right, text="Global Chat", font=("Arial", 12, "bold"), anchor="w", bg="white")
        self.context_label.pack(fill=tk.X, padx=10, pady=(5, 0))

        # Create scrollable message area with Canvas and Frame
        self.message_canvas = tk.Canvas(self.chat_right, bg="white")
        self.message_canvas.pack(padx=10, pady=5, fill=tk.BOTH, expand=True)
        
        # Scrollbar for canvas
        self.scrollbar = tk.Scrollbar(self.chat_right, orient=tk.VERTICAL, command=self.message_canvas.yview)
        self.scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        self.message_canvas.configure(yscrollcommand=self.scrollbar.set)
        
        # Frame inside canvas to hold messages
        self.messages_frame = tk.Frame(self.message_canvas, bg="white")
        self.canvas_window = self.message_canvas.create_window((0, 0), window=self.messages_frame, anchor="nw")
        
        # Store all messages for reference
        self.all_messages = []
        self.chat_messages = []
        self.active_chat_context = {"type": "GLOBAL", "name": None}
        self.selected_group = None  # Track the currently selected group
        self.current_group_member_window = None
        self.current_groups = []
        self.current_users = []

        # Bottom Input Bar
        self.input_frame = tk.Frame(self.chat_right)
        self.input_frame.pack(fill=tk.X, padx=10, pady=5)

        # 📎 Attachment Button (Clip Shape) for Advanced Features 
        self.attach_btn = tk.Button(self.input_frame, text="📎", command=self.open_file_dialog, 
                                    font=("Arial", 12), width=3)
        self.attach_btn.pack(side=tk.LEFT, padx=2)

        self.msg_entry = tk.Entry(self.input_frame, font=("Arial", 11))
        self.msg_entry.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=2)
        self.msg_entry.bind("<Return>", self.on_enter_key)

        self.send_btn = tk.Button(self.input_frame, text="Send", command=self.handle_send, 
                                  width=8, bg="#2196F3", fg="white")
        self.send_btn.pack(side=tk.RIGHT, padx=2)

    def update_canvas_scroll(self):
        """Update canvas scroll region after adding new message."""
        self.messages_frame.update_idletasks()
        scroll_height = self.messages_frame.winfo_reqheight()
        self.message_canvas.configure(scrollregion=self.message_canvas.bbox("all"))
        # Auto-scroll to bottom
        self.message_canvas.yview_moveto(1.0)

    def create_forward_button(self, message_text):
        """Create a forward button that opens forwarding dialog."""
        def forward_action():
            self.show_forward_dialog(message_text)
        return forward_action

    def show_forward_dialog(self, message_text):
        """Show dialog to select where to forward the message."""
        # Create a new window for forward options
        forward_window = tk.Toplevel(self.win)
        forward_window.title("Forward Message")
        forward_window.geometry("300x400")
        
        tk.Label(forward_window, text="Forward to:", font=("Arial", 12, "bold")).pack(pady=10)
        
        # Use currently cached group and user lists
        groups = list(self.current_groups)
        users = list(self.current_users)
        
        # Create frame for options
        options_frame = tk.Frame(forward_window)
        options_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # Add Global option
        global_btn = tk.Button(
            options_frame,
            text="📢 Global Chat",
            command=lambda: self.send_forwarded_message(message_text, "GLOBAL", forward_window),
            width=25,
            bg="#FF9800",
            fg="white"
        )
        global_btn.pack(pady=5, fill=tk.X)
        
        # Add Groups
        if groups:
            tk.Label(options_frame, text="Groups:", font=("Arial", 10, "bold")).pack(pady=(10, 5))
            for group in groups:
                group_btn = tk.Button(
                    options_frame,
                    text=f"👥 {group}",
                    command=lambda g=group: self.send_forwarded_message(message_text, f"GROUP_{g}", forward_window),
                    width=25,
                    bg="#9C27B0",
                    fg="white"
                )
                group_btn.pack(pady=3, fill=tk.X)
        
        # Add Users
        if users:
            tk.Label(options_frame, text="Users:", font=("Arial", 10, "bold")).pack(pady=(10, 5))
            for user in users:
                user_btn = tk.Button(
                    options_frame,
                    text=f"👤 {user}",
                    command=lambda u=user: self.send_forwarded_message(message_text, f"USER_{u}", forward_window),
                    width=25,
                    bg="#2196F3",
                    fg="white"
                )
                user_btn.pack(pady=3, fill=tk.X)
        
        # Cancel button
        cancel_btn = tk.Button(
            options_frame,
            text="Cancel",
            command=forward_window.destroy,
            width=25,
            bg="#757575",
            fg="white"
        )
        cancel_btn.pack(pady=10, fill=tk.X)

    def send_forwarded_message(self, message_text, target, forward_window):
        """Send the forwarded message to the server."""
        # Close the forward dialog
        forward_window.destroy()
        
        # Parse target
        if target == "GLOBAL":
            forward_cmd = f"FORWARD_GLOBAL:{message_text}"
            self.send_callback(forward_cmd)
            self.display_message(f"[Forwarded to Global] {message_text}", context_type="global")
        
        elif target.startswith("GROUP_"):
            group_name = target.replace("GROUP_", "")
            forward_cmd = f"FORWARD_GROUP:{group_name}:{message_text}"
            self.send_callback(forward_cmd)
            self.display_message(f"[Forwarded to {group_name}] {message_text}", context_type="group", context_target=group_name)
        
        elif target.startswith("USER_"):
            user_name = target.replace("USER_", "")
            forward_cmd = f"FORWARD_PRIVATE:{user_name}:{message_text}"
            self.send_callback(forward_cmd)
            self.display_message(f"[Forwarded to {user_name}] {message_text}", context_type="private", context_target=user_name)

    def on_enter_key(self, event):
        """Handle Enter key press in message entry."""
        self.handle_send()

    def handle_connect(self):
        username = self.name_entry.get()
        server_ip = self.server_ip_entry.get()
        server_port = self.server_port_entry.get()
        
        if not username:
            messagebox.showwarning("Error", "Please enter a username.")
            return
        
        if not server_ip:
            messagebox.showwarning("Error", "Please enter server IP address.")
            return
        
        if not server_port:
            messagebox.showwarning("Error", "Please enter server port.")
            return
        
        # Set server address in controller before connecting
        if self.server_controller:
            self.server_controller.set_server_address(server_ip, server_port)
        
        if self.connect_callback(username):
            self.user_label.configure(text=f"Logged in as {username}")
            self.login_frame.pack_forget()
            self.main_frame.pack(fill=tk.BOTH, expand=True)
        else:
            messagebox.showwarning("Error", "Could not connect to server. Check IP and Port.")

    def create_group_popup(self):
        """Asks for group name to fulfill Room Creation feature [cite: 9]"""
        g_name = simpledialog.askstring("New Group", "Enter Group Name:")
        if g_name:
            create_msg = f"CREATE_GROUP:{g_name}"
            self.send_callback(create_msg)

    def on_options_clicked(self):
        """Handle the options button click - show menu for selected group."""
        if self.selected_group:
            self.show_group_options(self.selected_group)

    def show_group_options(self, group_name):
        """Show options menu for the selected group."""
        menu = tk.Menu(self.win, tearoff=False)
        menu.add_command(label="View Members", command=lambda: self.send_callback(f"GET_GROUP_MEMBERS:{group_name}"))
        menu.add_separator()
        menu.add_command(label="Delete Group", command=lambda: self.delete_group(group_name))
        
        # Show menu at mouse position or at the button
        try:
            menu.tk_popup(self.win.winfo_pointerx(), self.win.winfo_pointery())
        except tk.TclError:
            pass

    def delete_group(self, group_name):
        """Delete a group."""
        if messagebox.askyesno("Delete Group", f"Are you sure you want to delete '{group_name}'?"):
            delete_msg = f"DELETE_GROUP:{group_name}"
            self.send_callback(delete_msg)

    def open_file_dialog(self):
        """Handles selecting images/videos for transmission [cite: 8, 17]"""
        file_path = filedialog.askopenfilename()
        if not file_path:
            return

        # Determine target from the current chat context
        target = "GLOBAL"
        if self.active_chat_context["type"] == "group":
            target = self.active_chat_context["name"]
        elif self.active_chat_context["type"] == "private":
            target = self.active_chat_context["name"]

        filename = os.path.basename(file_path)
        question = f"Send {filename} to {target}?"
        if messagebox.askyesno("Send File", question):
            self.file_callback(target, file_path)

    def handle_double_click(self, event):
        """No longer used with the custom sidebar layout."""
        pass

    def update_list_display(self, raw_list):
        """Maintains the list of active groups and users in the sidebar."""
        for widget in self.sidebar_inner.winfo_children():
            widget.destroy()

        groups = []
        users = []

        for item in raw_list:
            if item.startswith("G:"):
                groups.append(item[2:])
            elif item.startswith("U:"):
                users.append(item[2:])

        # Enable options button only if there are groups
        if groups:
            self.options_btn.config(state=tk.NORMAL)
        else:
            self.options_btn.config(state=tk.DISABLED)

        if groups:
            group_header = tk.Label(self.sidebar_inner, text="Groups", font=("Arial", 12, "bold"), bg="#f0f0f0")
            group_header.pack(fill=tk.X, padx=5, pady=(5, 2))
            for group_name in groups:
                row_frame = tk.Frame(self.sidebar_inner, bg="#f0f0f0")
                row_frame.pack(fill=tk.X, padx=5, pady=2)

                label = tk.Label(row_frame, text=group_name, font=("Arial", 11), anchor="w", bg="#f0f0f0", cursor="hand2")
                label.pack(side=tk.LEFT, fill=tk.X, expand=True)
                label.bind("<Button-1>", lambda event, g=group_name: self.set_active_chat_context("group", g))
                label.bind("<Double-1>", lambda event, g=group_name: self.set_active_chat_context("group", g))

        if users:
            user_header = tk.Label(self.sidebar_inner, text="Users", font=("Arial", 12, "bold"), bg="#f0f0f0")
            user_header.pack(fill=tk.X, padx=5, pady=(10, 2))
            for user_name in users:
                row_frame = tk.Frame(self.sidebar_inner, bg="#f0f0f0")
                row_frame.pack(fill=tk.X, padx=5, pady=2)

                label = tk.Label(row_frame, text=user_name, font=("Arial", 11), anchor="w", bg="#f0f0f0", cursor="hand2")
                label.pack(side=tk.LEFT, fill=tk.X, expand=True)
                label.bind("<Button-1>", lambda event, u=user_name: self.set_active_chat_context("private", u))
                label.bind("<Double-1>", lambda event, u=user_name: self.set_active_chat_context("private", u))

        self.current_groups = groups
        self.current_users = users
        self.sidebar_canvas.yview_moveto(0)

    def handle_send(self):
        """Sends real-time messages to the server [cite: 6]"""
        msg = self.msg_entry.get()
        if not msg:
            return

        # If currently chatting in a group or private context, prefix automatically
        if not msg.startswith("GROUP_MSG:") and not msg.startswith("/private:"):
            if self.active_chat_context["type"] == "group" and self.active_chat_context["name"]:
                msg = f"GROUP_MSG:{self.active_chat_context['name']}:{msg}"
            elif self.active_chat_context["type"] == "private" and self.active_chat_context["name"]:
                msg = f"/private:{self.active_chat_context['name']}:{msg}"

        self.send_callback(msg)
        
        # Display locally with formatting
        if msg.startswith("GROUP_MSG:"):
            parts = msg.split(":", 2)
            group_name = parts[1]
            message_content = parts[2]
            display_text = f"(Group {group_name}) You: {message_content}"
            self.display_message(display_text, context_type="group", context_target=group_name)
        
        elif msg.startswith("/private:"):
            parts = msg.split(":", 2)
            target_user = parts[1]
            message_content = parts[2]
            display_text = f"(Private to {target_user}) You: {message_content}"
            self.display_message(display_text, context_type="private", context_target=target_user)
        
        else:
            display_text = f"You: {msg}"
            self.display_message(display_text, context_type="global")
        
        self.msg_entry.delete(0, tk.END)

    def select_global_chat(self):
        """Switch view to global chat."""
        self.set_active_chat_context("GLOBAL", None)

    def handle_selection_change(self, event):
        """Legacy listbox selection handler; no-op with custom sidebar."""
        pass

    def set_active_chat_context(self, context_type, context_target):
        self.active_chat_context = {"type": context_type, "name": context_target}
        self.selected_group = context_target if context_type == "group" else None
        
        # Enable/disable options button based on group selection
        if context_type == "group":
            self.options_btn.config(state=tk.NORMAL)
        else:
            self.options_btn.config(state=tk.DISABLED)
        
        if context_type == "GLOBAL":
            self.context_label.configure(text="Global Chat")
        elif context_type == "group":
            self.context_label.configure(text=f"Group Chat: {context_target}")
        elif context_type == "private":
            self.context_label.configure(text=f"Private Chat: {context_target}")
        self.refresh_chat_view()

    def refresh_chat_view(self):
        """Show only messages relevant to the currently selected chat context."""
        for item in self.all_messages:
            item["frame"].pack_forget()

        for item in self.all_messages:
            if item["type"] == "global" and self.active_chat_context["type"] == "GLOBAL":
                item["frame"].pack(fill=tk.X, padx=5, pady=3)
            elif item["type"] == "group" and self.active_chat_context["type"] == "group" and item["target"] == self.active_chat_context["name"]:
                item["frame"].pack(fill=tk.X, padx=5, pady=3)
            elif item["type"] == "private" and self.active_chat_context["type"] == "private" and item["target"] == self.active_chat_context["name"]:
                item["frame"].pack(fill=tk.X, padx=5, pady=3)
            elif item["type"] == "system" and self.active_chat_context["type"] == "GLOBAL":
                item["frame"].pack(fill=tk.X, padx=5, pady=3)

        self.update_canvas_scroll()

    def infer_message_context(self, msg):
        """Infer message context from the text when not specified."""
        if msg.startswith("GROUP_SYSTEM:"):
            parts = msg.split(":", 2)
            if len(parts) > 1:
                return "group", parts[1]
        if msg.startswith("[") and "] " in msg:
            try:
                group_name = msg.split("]", 1)[0].lstrip("[")
                return "group", group_name
            except Exception:
                pass
        if msg.startswith("(Private)"):
            try:
                sender = msg.split(")", 1)[1].strip().split(":", 1)[0]
                return "private", sender
            except Exception:
                pass
        if msg.startswith("System:"):
            return "system", None
        return "global", None

    def show_group_options(self, group_name):
        """Open the small action dialog for a specific group."""
        if not group_name:
            return

        options_window = tk.Toplevel(self.win)
        options_window.title("Group Options")
        options_window.geometry("250x150")
        options_window.resizable(False, False)

        tk.Label(options_window, text=f"Group: {group_name}", font=("Arial", 11, "bold")).pack(pady=10)

        view_members_btn = tk.Button(
            options_window,
            text="View Members",
            command=lambda: self.request_group_members(group_name, options_window),
            width=20,
            bg="#4CAF50",
            fg="white"
        )
        view_members_btn.pack(pady=5)

        leave_group_btn = tk.Button(
            options_window,
            text="Leave Group",
            command=lambda: self.leave_group(group_name, options_window),
            width=20,
            bg="#F44336",
            fg="white"
        )
        leave_group_btn.pack(pady=5)

    def request_group_members(self, group_name, options_window):
        if options_window:
            options_window.destroy()
        self.current_group_member_window = tk.Toplevel(self.win)
        self.current_group_member_window.title("Group Members")
        self.current_group_member_window.geometry("300x250")
        tk.Label(self.current_group_member_window, text="Loading members...", font=("Arial", 11)).pack(pady=20)
        self.send_callback(f"REQUEST_GROUP_MEMBERS:{group_name}")

    def show_group_members(self, group_name, members):
        if self.current_group_member_window and self.current_group_member_window.winfo_exists():
            window = self.current_group_member_window
            for child in window.winfo_children():
                child.destroy()
            window.title(f"Members of {group_name}")
            tk.Label(window, text=f"{group_name}", font=("Arial", 12, "bold")).pack(pady=10)
            for member in members:
                tk.Label(window, text=member, font=("Arial", 10)).pack(anchor="w", padx=10)
        else:
            window = tk.Toplevel(self.win)
            window.title(f"Members of {group_name}")
            window.geometry("300x250")
            tk.Label(window, text=f"{group_name}", font=("Arial", 12, "bold")).pack(pady=10)
            for member in members:
                tk.Label(window, text=member, font=("Arial", 10)).pack(anchor="w", padx=10)

    def leave_group(self, group_name, options_window):
        if options_window:
            options_window.destroy()
        self.send_callback(f"GROUP_LEAVE:{group_name}")
        self.display_message(f"(Group {group_name}) System: You have left the group.", context_type="group", context_target=group_name)
        if self.active_chat_context["type"] == "group" and self.active_chat_context["name"] == group_name:
            self.set_active_chat_context("GLOBAL", None)

    def display_message(self, msg, context_type=None, context_target=None):
        """Displays incoming messages or alerts in real-time with forward button."""
        if context_type is None:
            context_type, context_target = self.infer_message_context(msg)

        # Play notification sound for messages
        if not msg.startswith("System:"):
            self.notification_manager.play_message_notification()
        
        # Create a frame for each message
        message_frame = tk.Frame(self.messages_frame, bg="white", relief=tk.FLAT, bd=1)
        
        # Create inner frame with message and button
        content_frame = tk.Frame(message_frame, bg="white")
        content_frame.pack(fill=tk.X, padx=5, pady=3)
        
        # Message text (read-only)
        message_text_widget = tk.Text(content_frame, height=2, width=60, font=("Arial", 11), bg="#F5F5F5", wrap=tk.WORD, state=tk.NORMAL)
        message_text_widget.insert(tk.END, msg)
        message_text_widget.configure(state=tk.DISABLED)
        message_text_widget.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=3)
        
        # Forward button (arrow icon)
        forward_callback = self.create_forward_button(msg)
        forward_btn = tk.Button(
            content_frame,
            text="➜",
            command=forward_callback,
            font=("Arial", 12),
            width=3,
            bg="#E3F2FD",
            fg="#1976D2",
            relief=tk.FLAT,
            cursor="hand2"
        )
        forward_btn.pack(side=tk.RIGHT, padx=3, pady=3)
        
        # Store message with its frame and context
        self.all_messages.append({
            "text": msg,
            "type": context_type,
            "target": context_target,
            "frame": message_frame
        })

        self.refresh_chat_view()

    def initiate_voice_call(self):
        """Initiate a voice call with the currently selected chat target."""
        try:
            if self.active_chat_context["type"] == "GLOBAL":
                target = "GLOBAL"
                call_type = "global"
            elif self.active_chat_context["type"] == "group":
                target = self.active_chat_context["name"]
                call_type = "group"
            elif self.active_chat_context["type"] == "private":
                target = self.active_chat_context["name"]
                call_type = "personal"
            else:
                messagebox.showwarning("Voice Call", "Please select a contact or group first!")
                return

            self.show_outgoing_call_window("voice", target, call_type)
            call_msg = VoiceCallSignaling.create_voice_call_request("You", target, call_type)
            self.send_callback(call_msg)
        except Exception as e:
            messagebox.showerror("Error", f"Error initiating voice call: {e}")

    def initiate_video_call(self):
        """Initiate a video call with the currently selected chat target."""
        try:
            if self.active_chat_context["type"] == "GLOBAL":
                target = "GLOBAL"
                call_type = "global"
            elif self.active_chat_context["type"] == "group":
                target = self.active_chat_context["name"]
                call_type = "group"
            elif self.active_chat_context["type"] == "private":
                target = self.active_chat_context["name"]
                call_type = "personal"
            else:
                messagebox.showwarning("Video Call", "Please select a contact or group first!")
                return

            self.show_outgoing_call_window("video", target, call_type)
            call_msg = VideoCallSignaling.create_video_call_request("You", target, call_type)
            self.send_callback(call_msg)
        except Exception as e:
            messagebox.showerror("Error", f"Error initiating video call: {e}")

    def show_outgoing_call_window(self, call_type, target, call_category):
        """Show outgoing call window with 'calling...' status."""
        self.active_call_window = tk.Toplevel(self.win)
        self.active_call_window.title(f"Outgoing {call_type.capitalize()} Call")
        self.active_call_window.geometry("400x300")
        
        # Icon
        if call_type == "voice":
            icon_text = "☎"
            color = "#4CAF50"
        else:
            icon_text = "📹"
            color = "#2196F3"
        
        tk.Label(self.active_call_window, text=icon_text, font=("Arial", 40), fg=color).pack(pady=10)
        
        # Target name
        tk.Label(self.active_call_window, text=f"Calling {target}...", font=("Arial", 14, "bold")).pack(pady=10)
        
        # Status
        self.call_status_label = tk.Label(self.active_call_window, text="Waiting for response...", font=("Arial", 11), fg="gray")
        self.call_status_label.pack(pady=10)
        
        # End call button
        end_btn = tk.Button(
            self.active_call_window,
            text="End Call",
            command=lambda: self.end_voice_video_call(call_type),
            font=("Arial", 12),
            width=15,
            bg="#F44336",
            fg="white"
        )
        end_btn.pack(pady=20)
        
        # Store current call info
        self.current_call_type = call_type
        self.call_in_progress = True

    def show_incoming_call_window(self, caller_name, call_type):
        """Show incoming call window at top of screen."""
        # Play ringing sound
        self.notification_manager.play_call_ringing()
        
        # Store caller information for rejection handling
        self.current_caller_name = caller_name
        
        # Create incoming call window at top
        self.incoming_call_window = tk.Toplevel(self.win)
        self.incoming_call_window.title(f"Incoming {call_type.capitalize()} Call")
        self.incoming_call_window.geometry("450x120")
        
        # Make window appear at top
        self.incoming_call_window.attributes('-topmost', True)
        
        # Icon
        if call_type == "voice":
            icon_text = "☎"
            color = "#4CAF50"
        else:
            icon_text = "📹"
            color = "#2196F3"
        
        # Top frame with icon and caller name
        top_frame = tk.Frame(self.incoming_call_window, bg=color)
        top_frame.pack(fill=tk.X, padx=0, pady=0)
        
        tk.Label(top_frame, text=icon_text, font=("Arial", 30), fg="white", bg=color).pack(side=tk.LEFT, padx=10, pady=5)
        
        # Caller name in big text
        tk.Label(top_frame, text=f"{caller_name} is calling...", font=("Arial", 12, "bold"), fg="white", bg=color).pack(side=tk.LEFT, padx=10, pady=5, expand=True)
        
        # Buttons frame at bottom
        buttons_frame = tk.Frame(self.incoming_call_window, bg="white")
        buttons_frame.pack(fill=tk.X, padx=10, pady=10)
        
        # Accept button (green)
        accept_btn = tk.Button(
            buttons_frame,
            text="Accept",
            command=lambda: self.accept_incoming_call(call_type, caller_name),
            font=("Arial", 11, "bold"),
            width=12,
            bg="#4CAF50",
            fg="white",
            relief=tk.RAISED,
            cursor="hand2"
        )
        accept_btn.pack(side=tk.LEFT, padx=5)
        
        # Reject button (red)
        reject_btn = tk.Button(
            buttons_frame,
            text="Reject",
            command=lambda: self.reject_incoming_call(call_type, caller_name),
            font=("Arial", 11, "bold"),
            width=12,
            bg="#F44336",
            fg="white",
            relief=tk.RAISED,
            cursor="hand2"
        )
        reject_btn.pack(side=tk.LEFT, padx=5)

    def accept_incoming_call(self, call_type, caller_name):
        """Accept an incoming call."""
        # Play acceptance sound
        self.notification_manager.play_call_accepted_sound()
        
        # Close incoming call window
        if self.incoming_call_window:
            self.incoming_call_window.destroy()
            self.incoming_call_window = None
        
        # Show active call window
        self.show_active_call_window(call_type, caller_name)
        
        # Send acceptance message
        if call_type == "voice":
            response_msg = VoiceCallSignaling.create_call_accepted(caller_name)
        else:
            response_msg = VideoCallSignaling.create_call_accepted(caller_name)
        
        self.send_callback(response_msg)
        self.display_message(f"System: You accepted {caller_name}'s {call_type} call.")

    def reject_incoming_call(self, call_type, caller_name):
        """Reject an incoming call."""
        # Play rejection sound
        self.notification_manager.play_call_rejected_sound()
        
        # Close incoming call window
        if self.incoming_call_window:
            self.incoming_call_window.destroy()
            self.incoming_call_window = None
        
        # Send rejection message with caller name
        if call_type == "voice":
            response_msg = VoiceCallSignaling.create_call_rejected(caller_name)
        else:
            response_msg = VideoCallSignaling.create_call_rejected(caller_name)
        
        self.send_callback(response_msg)
        self.display_message(f"System: You rejected {caller_name}'s {call_type} call.")

    def update_call_timer(self):
        """Update the call duration timer every second."""
        while self.call_timer_running:
            try:
                if self.call_start_time and self.call_duration_label:
                    elapsed_time = time.time() - self.call_start_time
                    
                    # Calculate minutes and seconds
                    minutes = int(elapsed_time) // 60
                    seconds = int(elapsed_time) % 60
                    
                    # Format time display
                    time_string = f"{minutes:02d}:{seconds:02d}"
                    
                    # Update label
                    try:
                        self.call_duration_label.config(text=time_string)
                    except Exception as e:
                        pass
                
                # Wait before next update
                time.sleep(1)
            except Exception as e:
                break

    def show_active_call_window(self, call_type, contact_name):
        """Show active call window with controls and timer."""
        self.active_call_window = tk.Toplevel(self.win)
        self.active_call_window.title(f"Active {call_type.capitalize()} Call")
        self.active_call_window.geometry("500x400")
        
        # Icon
        if call_type == "voice":
            icon_text = "☎"
            color = "#4CAF50"
        else:
            icon_text = "📹"
            color = "#2196F3"
        
        tk.Label(self.active_call_window, text=icon_text, font=("Arial", 50), fg=color).pack(pady=10)
        
        # Contact name and call duration
        tk.Label(self.active_call_window, text=f"Connected with {contact_name}", font=("Arial", 14, "bold")).pack(pady=5)
        
        self.call_duration_label = tk.Label(self.active_call_window, text="00:00", font=("Arial", 12), fg="gray")
        self.call_duration_label.pack(pady=5)
        
        # Video display area (if video call)
        if call_type == "video":
            video_frame = tk.Frame(self.active_call_window, bg="#000000", width=400, height=150)
            video_frame.pack(padx=10, pady=10, fill=tk.BOTH, expand=True)
            tk.Label(video_frame, text="[Video Stream]", font=("Arial", 12), fg="gray", bg="#000000").pack(expand=True)
        
        # Controls frame
        controls_frame = tk.Frame(self.active_call_window)
        controls_frame.pack(pady=10)
        
        # Mute button
        self.mute_btn = tk.Button(
            controls_frame,
            text="🔊 Mute",
            command=lambda: self.toggle_mute(call_type),
            font=("Arial", 11),
            width=10,
            bg="#FF9800",
            fg="white"
        )
        self.mute_btn.pack(side=tk.LEFT, padx=5)
        
        # Camera toggle button (only for video call)
        if call_type == "video":
            self.camera_btn = tk.Button(
                controls_frame,
                text="📷 Camera On",
                command=lambda: self.toggle_camera(call_type),
                font=("Arial", 11),
                width=12,
                bg="#2196F3",
                fg="white"
            )
            self.camera_btn.pack(side=tk.LEFT, padx=5)
            
            # Screen share button (only for video call)
            self.screen_btn = tk.Button(
                controls_frame,
                text="🖥 Share Screen",
                command=lambda: self.toggle_screen_share(call_type),
                font=("Arial", 11),
                width=14,
                bg="#9C27B0",
                fg="white"
            )
            self.screen_btn.pack(side=tk.LEFT, padx=5)
        
        # End call button
        end_btn = tk.Button(
            controls_frame,
            text="☎ End Call",
            command=lambda: self.end_voice_video_call(call_type),
            font=("Arial", 11),
            width=10,
            bg="#F44336",
            fg="white"
        )
        end_btn.pack(side=tk.LEFT, padx=5)
        
        # Store current call type
        self.current_call_type = call_type
        self.call_in_progress = True
        
        # Start call timer
        self.call_start_time = time.time()
        self.call_timer_running = True
        self.call_timer_thread = threading.Thread(target=self.update_call_timer, daemon=True)
        self.call_timer_thread.start()

    def toggle_mute(self, call_type):
        """Toggle microphone mute."""
        if call_type == "voice":
            is_muted = self.voice_call_manager.toggle_mute()
        else:
            is_muted = self.video_call_manager.toggle_mute()
        
        # Update button text
        mute_status = "Mute" if not is_muted else "Unmute"
        self.mute_btn.config(text=f"🔇 {mute_status}")
        
        # Display status
        status_msg = f"System: Microphone {'muted' if is_muted else 'unmuted'}"
        self.display_message(status_msg)

    def toggle_camera(self, call_type):
        """Toggle camera on/off for video calls."""
        if call_type == "video":
            is_camera_on = self.video_call_manager.toggle_camera()
            
            # Update button text
            camera_status = "Camera On" if is_camera_on else "Camera Off"
            self.camera_btn.config(text=f"📷 {camera_status}")
            
            # Display status
            status_msg = f"System: Camera {'turned on' if is_camera_on else 'turned off'}"
            self.display_message(status_msg)

    def toggle_screen_share(self, call_type):
        """Toggle screen sharing for video calls."""
        if call_type == "video":
            is_sharing = self.video_call_manager.toggle_screen_share()
            
            # Update button text
            share_status = "Stop Sharing" if is_sharing else "Share Screen"
            self.screen_btn.config(text=f"🖥 {share_status}")
            
            # Display status
            status_msg = f"System: Screen sharing {'started' if is_sharing else 'stopped'}"
            self.display_message(status_msg)

    def end_voice_video_call(self, call_type):
        """End the current voice or video call and show duration."""
        # Play call ended sound
        self.notification_manager.play_call_ended_sound()
        
        # Stop the timer
        self.call_timer_running = False
        
        # Calculate call duration
        call_duration = 0
        duration_string = "00:00"
        if self.call_start_time:
            call_duration = time.time() - self.call_start_time
            minutes = int(call_duration) // 60
            seconds = int(call_duration) % 60
            duration_string = f"{minutes:02d}:{seconds:02d}"
        
        # Close active call window
        if self.active_call_window:
            self.active_call_window.destroy()
            self.active_call_window = None
        
        # End call
        if call_type == "voice":
            self.voice_call_manager.end_voice_call()
            response_msg = f"VOICE_CALL_ENDED:You:{duration_string}"
        else:
            self.video_call_manager.end_video_call()
            response_msg = f"VIDEO_CALL_ENDED:You:{duration_string}"
        
        self.send_callback(response_msg)
        self.call_in_progress = False
        self.current_call_type = None
        self.current_caller_name = None
        
        # Display message with duration
        self.display_message(f"System: {call_type.capitalize()} call ended. Duration: {duration_string}")

    def handle_voice_call_request(self, message):
        """Handle incoming voice call request."""
        parsed = VoiceCallSignaling.parse_voice_call_request(message)
        if parsed:
            caller = parsed["sender"]
            self.show_incoming_call_window(caller, "voice")
            self.display_message(f"System: Incoming voice call from {caller}")

    def handle_video_call_request(self, message):
        """Handle incoming video call request."""
        parsed = VideoCallSignaling.parse_video_call_request(message)
        if parsed:
            caller = parsed["sender"]
            self.show_incoming_call_window(caller, "video")
            self.display_message(f"System: Incoming video call from {caller}")

    def handle_call_accepted(self, message, call_type):
        """Handle call acceptance."""
        acceptor = message.split(":")[1]
        if self.active_call_window:
            self.active_call_window.destroy()
        
        self.show_active_call_window(call_type, acceptor)
        self.display_message(f"System: {acceptor} accepted your {call_type} call.")

    def handle_call_rejected(self, message, call_type):
        """Handle call rejection."""
        # Play rejection sound
        self.notification_manager.play_call_rejected_sound()
        
        rejector = message.split(":")[1]
        if self.active_call_window:
            self.active_call_window.destroy()
            self.active_call_window = None
        
        self.call_in_progress = False
        self.current_call_type = None
        self.current_caller_name = None
        self.display_message(f"System: {rejector} rejected your {call_type} call.")

    def handle_call_ended(self, message, call_type):
        """Handle call ended notification with duration."""
        # Stop timer
        self.call_timer_running = False
        
        # Parse message format: CALL_TYPE_ENDED:ender:duration
        parts = message.split(":")
        ender = parts[1] if len(parts) > 1 else "Other user"
        duration = parts[2] if len(parts) > 2 else "00:00"
        
        # Close active call window
        if self.active_call_window:
            self.active_call_window.destroy()
            self.active_call_window = None
        
        self.call_in_progress = False
        self.current_call_type = None
        
        # Display message with duration
        self.display_message(f"System: {ender} ended the {call_type} call. Duration: {duration}")

    def start(self):
        self.win.mainloop()