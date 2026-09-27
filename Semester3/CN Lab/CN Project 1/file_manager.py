import os

class FileManager:
    @staticmethod
    def prepare_file_metadata(target, file_path):
        """
        Creates a header for the file transfer.
        Format: FILE_META:Target:FileName:FileSize
        """
        filename = os.path.basename(file_path)
        filesize = os.path.getsize(file_path)
        metadata_header = f"FILE_META:{target}:{filename}:{filesize}"
        return metadata_header, filesize

    @staticmethod
    def get_file_chunks(file_path, chunk_size=4096):
        """
        Read file in chunks for stable transmission 
        of images and videos over LAN/Wi-Fi.
        Returns list of chunks instead of using generator.
        """
        chunks = []
        try:
            file_handle = open(file_path, "rb")
            while True:
                chunk = file_handle.read(chunk_size)
                if not chunk:
                    break
                chunks.append(chunk)
            file_handle.close()
        except Exception as e:
            print(f"Error reading file: {e}")
        
        return chunks

    @staticmethod
    def save_incoming_file(filename, file_bytes):
        """
        Saves received binary data to the user's Documents folder.
        This simulates real-time file sharing.
        """
        try:
            # Get the standard path for the user's Documents folder
            user_home = os.path.expanduser("~")
            documents_folder = os.path.join(user_home, "Documents")
            doc_path = os.path.join(documents_folder, filename)
            
            # Create file and write bytes
            file_handle = open(doc_path, "wb")
            file_handle.write(file_bytes)
            file_handle.close()
            
            return doc_path
        except Exception as e:
            print(f"Error saving file: {e}")
            return None