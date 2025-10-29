import os
import tkinter as tk
from tkinter import filedialog, messagebox
from tkinter.ttk import Progressbar
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Protocol.KDF import PBKDF2
from Crypto.Util.Padding import pad, unpad

# Funzioni di utilità

def derive_key(password, salt, key_length=32):
    """Deriva una chiave dalla password usando PBKDF2."""
    return PBKDF2(password, salt, dkLen=key_length, count=100000)

def encrypt_file(file_path, password, progress_callback):
    """Cripta un singolo file."""
    try:
        salt = get_random_bytes(16)  # Genera un salt univoco
        key = derive_key(password, salt)
        cipher = AES.new(key, AES.MODE_CBC)

        with open(file_path, 'rb') as f:
            data = f.read()
        ciphertext = cipher.encrypt(pad(data, AES.block_size))

        with open(file_path + ".enc", 'wb') as f_enc:
            f_enc.write(salt + cipher.iv + ciphertext)

        os.remove(file_path)
        progress_callback(100)
        return True
    except Exception as e:
        print(f"Errore durante la cifratura di {file_path}: {e}")
        return False

def decrypt_file(file_path, password, progress_callback):
    """Decripta un singolo file."""
    try:
        with open(file_path, 'rb') as f_enc:
            salt = f_enc.read(16)  # Leggi il salt dai primi 16 byte
            iv = f_enc.read(16)    # Leggi l'IV successivo
            ciphertext = f_enc.read()

        key = derive_key(password, salt)
        cipher = AES.new(key, AES.MODE_CBC, iv=iv)
        data = unpad(cipher.decrypt(ciphertext), AES.block_size)

        original_file_path = file_path[:-4]  # Rimuovi ".enc"
        with open(original_file_path, 'wb') as f:
            f.write(data)

        os.remove(file_path)
        progress_callback(100)
        return True
    except Exception as e:
        print(f"Errore durante la decrittazione di {file_path}: {e}")
        return False

def process_directory(directory, password, mode, progress_callback):
    """Processa tutti i file in una directory."""
    files = []
    for root, _, filenames in os.walk(directory):
        for file in filenames:
            file_path = os.path.join(root, file)
            if mode == 'encrypt' and not file.endswith('.enc'):
                files.append(file_path)
            elif mode == 'decrypt' and file.endswith('.enc'):
                files.append(file_path)

    total_files = len(files)
    for index, file_path in enumerate(files, start=1):
        progress_callback(int((index / total_files) * 100))
        if mode == 'encrypt':
            encrypt_file(file_path, password, lambda x: None)
        elif mode == 'decrypt':
            decrypt_file(file_path, password, lambda x: None)

# Interfaccia grafica
class CryptoApp:
    def __init__(self, root):
        self.root = root
        self.root.title("CryptoLuca 4")
        self.root.iconbitmap("lock.ico")
        self.file_or_dir = None

        # Layout
        self.label = tk.Label(root, text="Seleziona un file o una directory:")
        self.label.pack(pady=5)

        self.path_entry = tk.Entry(root, width=50)
        self.path_entry.pack(pady=5)

        self.browse_button = tk.Button(root, text="Sfoglia", command=self.browse_file_or_directory)
        self.browse_button.pack(pady=5)

        self.label_password = tk.Label(root, text="Inserisci la password (almeno 8 caratteri):")
        self.label_password.pack(pady=5)

        self.password_frame = tk.Frame(root)
        self.password_frame.pack(pady=5)

        self.password_entry = tk.Entry(self.password_frame, show="*", width=30)
        self.password_entry.pack(side=tk.LEFT, padx=5)

        self.show_password_var = tk.IntVar()
        self.show_password_check = tk.Checkbutton(
            self.password_frame, text="Mostra", variable=self.show_password_var, command=self.toggle_password
        )
        self.show_password_check.pack(side=tk.LEFT)

        self.encrypt_button = tk.Button(root, text="Cripta", command=lambda: self.run_crypto('encrypt'))
        self.encrypt_button.pack(pady=5)

        self.decrypt_button = tk.Button(root, text="Decripta", command=lambda: self.run_crypto('decrypt'))
        self.decrypt_button.pack(pady=5)

        self.progress = Progressbar(root, orient=tk.HORIZONTAL, length=300, mode='determinate')
        self.progress.pack(pady=10)

    def toggle_password(self):
        if self.show_password_var.get():
            self.password_entry.config(show="")
        else:
            self.password_entry.config(show="*")

    def browse_file_or_directory(self):
        path = filedialog.askopenfilename()
        if not path:
            path = filedialog.askdirectory()
        self.path_entry.delete(0, tk.END)
        self.path_entry.insert(0, path)

    def update_progress(self, value):
        self.progress["value"] = value
        self.root.update_idletasks()

    def run_crypto(self, mode):
        path = self.path_entry.get().strip()
        password = self.password_entry.get().strip()

        if not os.path.exists(path):
            messagebox.showerror("Errore", "Percorso non valido!")
            return

        if len(password) < 8:
            messagebox.showerror("Errore", "La password deve essere lunga almeno 8 caratteri!")
            return

        self.progress["value"] = 0
        if os.path.isfile(path):
            success = False
            if mode == 'encrypt':
                success = encrypt_file(path, password, self.update_progress)
            elif mode == 'decrypt':
                success = decrypt_file(path, password, self.update_progress)

            if success:
                messagebox.showinfo("Successo", f"File {mode}ed con successo!")
            else:
                messagebox.showerror("Errore", f"Errore durante il {mode} del file.")

        elif os.path.isdir(path):
            process_directory(path, password, mode, self.update_progress)
            messagebox.showinfo("Successo", f"Directory {mode}ed con successo!")

if __name__ == "__main__":
    root = tk.Tk()
    app = CryptoApp(root)
    root.mainloop()