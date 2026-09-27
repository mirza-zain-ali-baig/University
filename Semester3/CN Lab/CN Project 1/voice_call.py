import threading
import time

class VoiceCallManager:
    """Manages voice call connections between clients."""
    
    def __init__(self):
        # Track current call state
        self.current_call = None
        self.is_muted = False
        self.call_active = False
        self.call_type = None  # "personal", "group", "global"
        self.call_participants = []
        
    def initiate_voice_call(self, target_user, call_type):
        """
        Start a voice call request to a target.
        call_type: "personal" for 1-to-1, "group" for group, "global" for broadcast
        """
        call_request = {
            "type": "VOICE_CALL_REQUEST",
            "target": target_user,
            "call_type": call_type,
            "timestamp": time.time()
        }
        return call_request
    
    def accept_voice_call(self, caller_name, call_type):
        """Accept an incoming voice call."""
        self.current_call = {
            "caller": caller_name,
            "type": call_type,
            "started_at": time.time(),
            "is_active": True
        }
        self.call_active = True
        return "VOICE_CALL_ACCEPTED"
    
    def reject_voice_call(self):
        """Reject an incoming voice call."""
        self.current_call = None
        self.call_active = False
        return "VOICE_CALL_REJECTED"
    
    def end_voice_call(self):
        """End the current active voice call."""
        if self.current_call:
            call_duration = time.time() - self.current_call["started_at"]
            self.current_call = None
            self.call_active = False
            return call_duration
        return 0
    
    def toggle_mute(self):
        """Toggle microphone mute state."""
        self.is_muted = not self.is_muted
        return self.is_muted
    
    def get_mute_status(self):
        """Get current mute status."""
        return self.is_muted
    
    def get_call_status(self):
        """Get current call status."""
        if self.call_active and self.current_call:
            return {
                "active": True,
                "caller": self.current_call["caller"],
                "type": self.current_call["type"],
                "duration": time.time() - self.current_call["started_at"],
                "muted": self.is_muted
            }
        return {
            "active": False,
            "caller": None,
            "type": None,
            "duration": 0,
            "muted": self.is_muted
        }


class CallSignaling:
    """Handles call signaling protocol messages."""
    
    @staticmethod
    def create_voice_call_request(sender, target, call_type):
        """
        Create a voice call request message.
        Format: VOICE_CALL_REQUEST:sender:target:type
        type can be: personal, group, global
        """
        message = f"VOICE_CALL_REQUEST:{sender}:{target}:{call_type}"
        return message
    
    @staticmethod
    def create_call_ringing(caller):
        """
        Create a call ringing notification.
        Format: VOICE_CALL_RINGING:caller
        """
        message = f"VOICE_CALL_RINGING:{caller}"
        return message
    
    @staticmethod
    def create_call_accepted(acceptor):
        """
        Create a call accepted notification.
        Format: VOICE_CALL_ACCEPTED:acceptor
        """
        message = f"VOICE_CALL_ACCEPTED:{acceptor}"
        return message
    
    @staticmethod
    def create_call_rejected(rejector):
        """
        Create a call rejected notification.
        Format: VOICE_CALL_REJECTED:rejector
        """
        message = f"VOICE_CALL_REJECTED:{rejector}"
        return message
    
    @staticmethod
    def create_call_ended(ender):
        """
        Create a call ended notification.
        Format: VOICE_CALL_ENDED:ender
        """
        message = f"VOICE_CALL_ENDED:{ender}"
        return message
    
    @staticmethod
    def parse_voice_call_request(message):
        """Parse voice call request message."""
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


class AudioStreamManager:
   
    
    def __init__(self):
        self.is_streaming = False
        self.stream_data = []
        self.audio_chunks = []
        self.audio_interface = None
        self.audio_stream = None
        self.playback_stream = None
        
        # Audio configuration
        self.audio_format = 8  # pyaudio.paInt16 = 8
        self.audio_channels = 1
        self.audio_sample_rate = 16000
        self.audio_chunk_size = 1024
        
        # Try to initialize pyaudio
        try:
            import pyaudio  # type: ignore
            self.audio_interface = pyaudio.PyAudio()
            self.pyaudio_available = True
        except ImportError:
            self.pyaudio_available = False
            self.audio_interface = None
    
    def start_audio_capture(self):
        """Start capturing audio from microphone."""
        if not self.pyaudio_available:
            return False
        
        try:
            self.audio_stream = self.audio_interface.open(
                format=self.audio_format,
                channels=self.audio_channels,
                rate=self.audio_sample_rate,
                input=True,
                frames_per_buffer=self.audio_chunk_size
            )
            self.is_streaming = True
            return True
        except Exception as e:
            self.is_streaming = False
            return False
    
    def start_audio_playback(self):
        """Start audio playback stream."""
        if not self.pyaudio_available:
            return False
        
        try:
            self.playback_stream = self.audio_interface.open(
                format=self.audio_format,
                channels=self.audio_channels,
                rate=self.audio_sample_rate,
                output=True,
                frames_per_buffer=self.audio_chunk_size
            )
            return True
        except Exception as e:
            return False
    
    def stop_audio_capture(self):
        """Stop capturing audio."""
        self.is_streaming = False
        if self.audio_stream:
            try:
                self.audio_stream.stop_stream()
                self.audio_stream.close()
                self.audio_stream = None
            except Exception as e:
                pass
        return True
    
    def stop_audio_playback(self):
        """Stop audio playback."""
        if self.playback_stream:
            try:
                self.playback_stream.stop_stream()
                self.playback_stream.close()
                self.playback_stream = None
            except Exception as e:
                pass
        return True
    
    def get_audio_chunk(self, chunk_size=1024):
        """
        Get a chunk of audio data from microphone.
        Returns audio bytes that can be sent over network.
        """
        if not self.is_streaming or not self.audio_stream:
            return None
        
        try:
            audio_chunk = self.audio_stream.read(self.audio_chunk_size, exception_on_overflow=False)
            return audio_chunk
        except Exception as e:
            return None
    
    def play_audio_chunk(self, audio_data):
        """
        Play received audio chunk through speakers.
        """
        if not audio_data or not self.playback_stream:
            return False
        
        try:
            self.playback_stream.write(audio_data)
            return True
        except Exception as e:
            return False
