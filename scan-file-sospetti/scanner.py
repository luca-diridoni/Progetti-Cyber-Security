#!/usr/bin/env python3
# simple_scanner.py
# Scansione base: chiede un percorso, trova file con estensioni sospette e salva report .txt
# Uso: python simple_scanner.py

import os
from pathlib import Path

SUSPICIOUS_EXT = {
    ".exe", ".bat", ".cmd", ".com", ".msi", ".jar",
    ".ps1", ".vbs", ".js", ".wsf", ".hta", ".scr",
    ".pif", ".sh", ".vbe",
    # documenti con macro
    ".docm", ".xlsm", ".pptm"
}

MAX_RESULTS = 100
OUTPUT_FILE = "file_sospetti_trovati.txt"

def scan_folder(folder_path):
    found = []
    for root, dirs, files in os.walk(folder_path):
        for fname in files:
            try:
                p = Path(root) / fname
                if p.suffix.lower() in SUSPICIOUS_EXT:
                    found.append(str(p.resolve()))
                    if len(found) >= MAX_RESULTS:
                        return found
            except Exception:
                # ignora file non accessibili e continua
                continue
    return found

def main():
    folder = input("Inserisci il percorso della cartella da scansionare: ").strip()
    if not folder:
        print("Percorso vuoto — esco.")
        return
    p = Path(folder)
    if not p.exists() or not p.is_dir():
        print("Percorso non valido o non è una cartella.")
        return

    print(f"Scansione in corso di: {p} ...")
    results = scan_folder(str(p))

    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        f.write(f"Report scanner base - cartella: {p}\n")
        f.write(f"Totale risultati (mostrati max {MAX_RESULTS}): {len(results)}\n\n")
        for r in results:
            f.write(r + "\n")

    print(f"Scansione completata. Trovati {len(results)} file. Report salvato in: {OUTPUT_FILE}")

if __name__ == "__main__":
    main()
