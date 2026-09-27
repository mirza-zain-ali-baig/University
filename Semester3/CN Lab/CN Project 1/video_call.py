import threading
import time

class VideoCallManager:
    """Manages video call connections between clients."""
    
    def __init__(self):
        # Track current call state
        self.current_call = None
        self.is_muted = False
        self.is_camera_on = True
        self.is_screen_sharing = False
        self.call_active = False
        self.call_type = None  # "personal", "group", "global"
        self.call_participants = []
        
    def initiate_video_call(self, target_user, call_type):
        """
        Start a video call request to a target.
        call_type: "personal" for 1-to-1, "group" for group, "global" for broadcast
        """
        call_request = {
            "type": "VIDEO_CALL_REQUEST",
            "target": target_user,
            "call_type": call_type,
            "timestamp": time.time()
        }
        return call_request
    
    def accept_video_call(self, caller_name, call_type):
        """Accept an incoming video call."""
        self.current_call = {
            "caller": caller_name,
            "type": call_type,
            "started_at": time.time(),
            "is_active": True
        }
        self.call_active = True
        return "VIDEO_CALL_ACCEPTED"
    
    def reject_video_call(self):
        """Reject an incoming video call."""
        self.current_call = None
        self.call_active = False
        return "VIDEO_CALL_REJECTED"
    
    def end_video_call(self):
        """End the current active video call."""
        if self.current_call:
            call_duration = time.time() - self.current_call["started_at"]
            self.current_call = None
            self.call_active = False
            self.is_screen_sharing = False
            return call_duration
        return 0
    
    def toggle_mute(self):
        """Toggle microphone mute state."""
        self.is_muted = not self.is_muted
        return self.is_muted
    
    def toggle_camera(self):
        """Toggle camera on/off."""
        self.is_camera_on = not self.is_camera_on
        return self.is_camera_on
    
    def toggle_screen_share(self):
        """Toggle screen sharing."""
        self.is_screen_sharing = not self.is_screen_sharing
        return self.is_screen_sharing
    
    def get_mute_status(self):
        """Get current mute status."""
        return self.is_muted
    
    def get_camera_status(self):
        """Get current camera status."""
        return self.is_camera_on
    
    def get_screen_share_status(self):
        """Get current screen sharing status."""
        return self.is_screen_sharing
    
    def get_call_status(self):
        """Get current call status."""
        if self.call_active and self.current_call:
            return {
                "active": True,
                "caller": self.current_call["caller"],
                "type": self.current_call["type"],
                "duration": time.time() - self.current_call["started_at"],
                "muted": self.is_muted,
                "camera_on": self.is_camera_on,
                "screen_sharing": self.is_screen_sharing
            }
        return {
            "active": False,
            "caller": None,
            "type": None,
            "duration": 0,
            "muted": self.is_muted,
            "camera_on": self.is_camera_on,
            "screen_sharing": self.is_screen_sharing
        }


class CallSignaling:
    """Handles call signaling protocol messages."""
    
    @staticmethod
    def create_video_call_request(sender, target, call_type):
        """
        Create a video call request message.
        Format: VIDEO_CALL_REQUEST:sender:target:type
        type can be: personal, group, global
        """
        message = f"VIDEO_CALL_REQUEST:{sender}:{target}:{call_type}"
        return message
    
    @staticmethod
    def create_call_ringing(caller):
        """
        Create a call ringing notification.
        Format: VIDEO_CALL_RINGING:caller
        """
        message = f"VIDEO_CALL_RINGING:{caller}"
        return message
    
    @staticmethod
    def create_call_accepted(acceptor):
        """
        Create a call accepted notification.
        Format: VIDEO_CALL_ACCEPTED:acceptor
        """
        message = f"VIDEO_CALL_ACCEPTED:{acceptor}"
        return message
    
    @staticmethod
    def create_call_rejected(rejector):
        """
        Create a call rejected notification.
        Format: VIDEO_CALL_REJECTED:rejector
        """
        message = f"VIDEO_CALL_REJECTED:{rejector}"
        return message
    
    @staticmethod
    def create_call_ended(ender):
        """
        Create a call ended notification.
        Format: VIDEO_CALL_ENDED:ender
        """
        message = f"VIDEO_CALL_ENDED:{ender}"
        return message
    
    @staticmethod
    def parse_video_call_request(message):
        """Parse video call request message."""
        parts = message.split(":")
        if len(parts) >= 4:
            sender = parts[1]
            target = parts[2]
            call_type = parts[3]
            return {
                "sender": sender,
                "target": target,
                "type": call_type
            }
        return None


class VideoStreamManager:
    """Manages video streaming with real video capture and screen sharing."""
    
    def __init__(self):
        self.is_streaming = False
        self.video_frames = []
        self.screen_capture_active = False
        self.video_capture = None
        self.screen_capturer = None
        
        # Video configuration
        self.video_width = 320
        self.video_height = 240
        self.video_fps = 10
        
        # Try to initialize opencv
        try:
            import cv2  # type: ignore
            self.cv2_available = True
            self.cv2 = cv2
        except ImportError:
            self.cv2_available = False
            self.cv2 = None
        
        # Try to initialize mss for screen capture
        try:
            import mss  # type: ignore
            self.mss_available = True
            self.mss = mss
        except ImportError:
            self.mss_available = False
            self.mss = None
    
    def start_video_capture(self):
        """Start capturing video from camera using opencv."""
        if not self.cv2_available:
            return False
        
        try:
            self.video_capture = self.cv2.VideoCapture(0)
            
            # Set video properties
            self.video_capture.set(self.cv2.CAP_PROP_FRAME_WIDTH, self.video_width)
            self.video_capture.set(self.cv2.CAP_PROP_FRAME_HEIGHT, self.video_height)
            self.video_capture.set(self.cv2.CAP_PROP_FPS, self.video_fps)
            
            self.is_streaming = True
            return True
        except Exception as e:
            self.is_streaming = False
            return False
    
    def stop_video_capture(self):
        """Stop capturing video from camera."""
        self.is_streaming = False
        if self.video_capture:
            try:
                self.video_capture.release()
                self.video_capture = None
            except Exception as e:
                pass
        return True
    
    def get_video_frame(self):
        """
        Get a frame from camera.
        Returns encoded frame data as bytes.
        """
        if not self.is_streaming or not self.video_capture:
            return None
        
        try:
            success, frame = self.video_capture.read()
            
            if not success:
                return None
            
            # Encode frame as JPEG bytes
            success, encoded_frame = self.cv2.imencode('.jpg', frame, [self.cv2.IMWRITE_JPEG_QUALITY, 80])
            
            if success:
                frame_bytes = encoded_frame.tobytes()
                return frame_bytes
            
            return None
        except Exception as e:
            return None
    
    def display_video_frame(self, frame_data):
        """
        Display received video frame.
        This should be called by GUI with the encoded frame data.
        """
        if not frame_data or not self.cv2_available:
            return False
        
        try:
            # Decode frame from bytes
            import numpy  # type: ignore
            frame_array = numpy.frombuffer(frame_data, dtype=numpy.uint8)
            frame = self.cv2.imdecode(frame_array, self.cv2.IMREAD_COLOR)
            
            if frame is not None:
                return frame
            
            return None
        except Exception as e:
            return None
    
    def start_screen_capture(self):
        """Start capturing screen for screen sharing using mss."""
        if not self.mss_available:
            return False
        
        try:
            self.screen_capturer = self.mss.mss()
            self.screen_capture_active = True
            return True
        except Exception as e:
            self.screen_capture_active = False
            return False
    
    def stop_screen_capture(self):
        """Stop capturing screen."""
        self.screen_capture_active = False
        if self.screen_capturer:
            try:
                self.screen_capturer.close()
                self.screen_capturer = None
            except Exception as e:
                pass
        return True
    
    def get_screen_frame(self):
        """
        Get a frame from screen capture.
        Returns encoded screen data as bytes.
        """
        if not self.screen_capture_active or not self.screen_capturer:
            return None
        
        try:
            # Get primary monitor
            monitor = self.screen_capturer.monitors[1]
            
            # Capture screen
            screenshot = self.screen_capturer.grab(monitor)
            
            # Convert to numpy array
            import numpy  # type: ignore
            frame = numpy.array(screenshot)
            
            # Encode as JPEG
            success, encoded_frame = self.cv2.imencode('.jpg', frame, [self.cv2.IMWRITE_JPEG_QUALITY, 60])
            
            if success:
                frame_bytes = encoded_frame.tobytes()
                return frame_bytes
            
            return None
        except Exception as e:
            return None
    
    def display_screen_frame(self, frame_data):
        """
        Display received screen frame.
        """
        if not frame_data or not self.cv2_available:
            return False
        
        try:
            # Decode frame from bytes
            import numpy  # type: ignore
            frame_array = numpy.frombuffer(frame_data, dtype=numpy.uint8)
            frame = self.cv2.imdecode(frame_array, self.cv2.IMREAD_COLOR)
            
            if frame is not None:
                return frame
            
            return None
        except Exception as e:
            return None
