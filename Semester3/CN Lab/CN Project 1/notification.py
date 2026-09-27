import os
import sys

class NotificationManager:
    """Manages all notification sounds and alerts for the chat application."""
    
    def __init__(self):
        # Check if winsound is available (Windows only)
        self.winsound_available = False
        try:
            import winsound
            self.winsound_available = True
            self.winsound = winsound
        except ImportError:
            self.winsound_available = False
    
    def play_message_notification(self):
        """
        Play a simple beep sound when a message is received.
        This is a short, single beep to notify the user of a new message.
        """
        if self.winsound_available:
            try:
                # Frequency: 1000 Hz (beep), Duration: 200 milliseconds
                self.winsound.Beep(1000, 200)
            except Exception as e:
                pass
        else:
            # Fallback for non-Windows systems
            self.play_fallback_beep()
    
    def play_call_ringing(self):
        """
        Play a ringing sound when an incoming call is received.
        This is a repeating pattern to simulate a phone ringing.
        """
        if self.winsound_available:
            try:
                # Ring pattern: multiple beeps with intervals
                # Simulates phone ringing sound
                for ring_count in range(3):
                    # First beep
                    self.winsound.Beep(800, 300)
                    # Pause
                    self.winsound.Sleep(200)
                    # Second beep
                    self.winsound.Beep(800, 300)
                    # Longer pause between rings
                    self.winsound.Sleep(500)
            except Exception as e:
                pass
        else:
            # Fallback for non-Windows systems
            self.play_fallback_ringing()
    
    def play_call_accepted_sound(self):
        """
        Play a sound when a call is accepted.
        This is a positive confirmation sound.
        """
        if self.winsound_available:
            try:
                # Ascending beeps to indicate acceptance
                self.winsound.Beep(700, 150)
                self.winsound.Sleep(100)
                self.winsound.Beep(900, 150)
                self.winsound.Sleep(100)
                self.winsound.Beep(1100, 150)
            except Exception as e:
                pass
        else:
            self.play_fallback_acceptance()
    
    def play_call_rejected_sound(self):
        """
        Play a sound when a call is rejected.
        This is a negative/error sound.
        """
        if self.winsound_available:
            try:
                # Descending beeps to indicate rejection
                self.winsound.Beep(1100, 150)
                self.winsound.Sleep(100)
                self.winsound.Beep(900, 150)
                self.winsound.Sleep(100)
                self.winsound.Beep(700, 150)
            except Exception as e:
                pass
        else:
            self.play_fallback_rejection()
    
    def play_call_ended_sound(self):
        """
        Play a sound when a call ends.
        This is a short notification sound.
        """
        if self.winsound_available:
            try:
                # Two beeps to indicate call end
                self.winsound.Beep(1000, 100)
                self.winsound.Sleep(150)
                self.winsound.Beep(1000, 100)
            except Exception as e:
                pass
        else:
            self.play_fallback_end()
    
    def play_fallback_beep(self):
        """
        Fallback for non-Windows systems - use built-in sound.
        """
        try:
            # Use system beep
            print('\a', end='', flush=True)
        except Exception as e:
            pass
    
    def play_fallback_ringing(self):
        """
        Fallback for non-Windows systems - ring pattern using system beep.
        """
        try:
            for ring_count in range(3):
                print('\a', end='', flush=True)
                # Note: timing not precise on non-Windows, but provides audio feedback
        except Exception as e:
            pass
    
    def play_fallback_acceptance(self):
        """
        Fallback for non-Windows systems - acceptance sound using system beep.
        """
        try:
            print('\a', end='', flush=True)
        except Exception as e:
            pass
    
    def play_fallback_rejection(self):
        """
        Fallback for non-Windows systems - rejection sound using system beep.
        """
        try:
            print('\a', end='', flush=True)
        except Exception as e:
            pass
    
    def play_fallback_end(self):
        """
        Fallback for non-Windows systems - end call sound using system beep.
        """
        try:
            print('\a', end='', flush=True)
        except Exception as e:
            pass


# Global notification manager instance
global_notification_manager = NotificationManager()
