# Chat Application Guide

## Overview
This application uses a Python server and client GUI to provide:
- Global chat for all connected users
- Private chat between two users
- Group chat that appears only when selected
- Per-group options with a small three-dot button
- File sending, voice calls, and video call signaling

## Requirements
- Python 3.8+ installed on Windows
- No external packages are required for the core chat app

## How to Run
1. Open a terminal in `C:\Users\Rizvi\Desktop\CN Lab\Practise\CN Latest`
2. Start the server:
   ```bash
   python server.py
   ```
3. Open a second terminal and start the client:
   ```bash
   python client.py
   ```
4. Repeat step 3 for each additional client session.

## Usage
1. Enter a unique username and click **Login**.
2. Use the sidebar to choose:
   - **Global Chat** for all messages
   - a **Group** to see only group messages
   - a **User** to see private messages with that user
3. Click the small `⋮` button next to each group to view members or leave the group.
4. Type a message and click **Send** or press **Enter**.
5. The username appears at the top center of the interface after login.

## Notes
- Group messages are visible only when the group is selected.
- Private messages appear only in the private chat with that user.
- If there is no conversation in a chat, the right panel remains empty until a message arrives.
- The global chat is shared among all clients.
