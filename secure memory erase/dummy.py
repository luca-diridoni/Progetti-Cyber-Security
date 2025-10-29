import tkinter as tk
from tkinter import ttk

def generate_command():
    # Recupera i valori inseriti
    drive = drive_var.get()  # Lettera del disco (es: C)
    size_value = entry_size.get()  # Dimensione inserita
    unit = unit_var.get()  # Unità selezionata
    
    try:
        size_num = float(size_value)
    except ValueError:
        result_var.set("Errore: inserire un numero valido per la dimensione!")
        return
    
    # Dizionario di conversione in byte (usando il sistema decimale)
    conversion = {
        "TB": 10**12,
        "GB": 10**9,
        "MB": 10**6,
        "KB": 10**3,
        "Byte": 1
    }
    
    # Calcola la dimensione in byte
    bytes_size = int(size_num * conversion[unit])
    
    # Crea il comando completo
    command = f"fsutil file createnew {drive}:\\dummy.dat {bytes_size}"
    
    result_var.set(command)

# Creazione della finestra principale
root = tk.Tk()
root.title("Generatore di Comando fsutil")

# Variabili Tkinter
drive_var = tk.StringVar(value="C")
unit_var = tk.StringVar(value="GB")
result_var = tk.StringVar()

# Creazione del menu a tendina per la lettera del disco
tk.Label(root, text="Seleziona la lettera del disco:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
drive_options = [chr(i) for i in range(65, 91)]  # Genera la lista A-Z
drive_menu = ttk.Combobox(root, textvariable=drive_var, values=drive_options, state="readonly")
drive_menu.grid(row=0, column=1, padx=5, pady=5)

# Campo per inserire la dimensione
tk.Label(root, text="Inserisci la dimensione:").grid(row=1, column=0, sticky="w", padx=5, pady=5)
entry_size = tk.Entry(root)
entry_size.grid(row=1, column=1, padx=5, pady=5)

# Menu a tendina per l'unità di misura
tk.Label(root, text="Seleziona l'unità di misura:").grid(row=2, column=0, sticky="w", padx=5, pady=5)
unit_options = ["TB", "GB", "MB", "KB", "Byte"]
unit_menu = ttk.Combobox(root, textvariable=unit_var, values=unit_options, state="readonly")
unit_menu.grid(row=2, column=1, padx=5, pady=5)

# Bottone per generare il comando
generate_button = tk.Button(root, text="Genera Comando", command=generate_command)
generate_button.grid(row=3, column=0, columnspan=2, padx=5, pady=10)

# Campo per visualizzare il comando generato
tk.Label(root, text="Comando:").grid(row=4, column=0, sticky="w", padx=5, pady=5)
result_entry = tk.Entry(root, textvariable=result_var, width=50)
result_entry.grid(row=4, column=1, padx=5, pady=5)

# Avvio dell'interfaccia grafica
root.mainloop()
