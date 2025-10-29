# Scanner di file sospetti

## Descrizione
Questo progetto è un **mini-script Python** che esegue una scansione ricorsiva di base di una cartella (e sottocartelle), individuando file con **estensioni sospette** comunemente associate a eseguibili, script o documenti con macro.  
Il programma genera un **report testuale** con la lista dei file trovati.

## Estensioni sospette
.exe, .bat, .cmd, .com, .msi, .jar, .ps1, .vbs, .js, .wsf, .hta, .scr, .pif, .sh, .vbe, .docm, .xlsm, .pptm

## Scopo
- Pratica personale di scripting Python.  
- Esercitazione su gestione file, percorsi e input dell’utente.  
- Introduzione ai concetti base di sicurezza informatica (identificazione file potenzialmente pericolosi).

## Funzionalità principali
- Chiede all’utente il percorso di una cartella da scansionare.  
- Trova file con estensioni sospette (`.exe`, `.bat`, `.docm`, `.xlsm`, ecc.).  
- Limita i risultati a un massimo di 100 file.
- Salva il report in un file di testo (`file_sospetti_trovati.txt`).  

## Requisiti
- Python 3.x  
- Moduli standard (`os`, `pathlib`) — nessuna libreria esterna necessaria.

## Uso
1. Aprire il terminale o prompt dei comandi.  
2. Eseguire lo script
3. Inserire il percorso da scansionare
4. Verrà creato l'elenco
