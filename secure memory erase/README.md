## Descrizione
Questo script Python fornisce un'interfaccia grafica (Tkinter) per generare un comando Windows fsutil file createnew che crea un file vuoto (dummy.dat) di dimensione scelta su una lettera di unità selezionata.

## Scopo
Dopo l'eliminazione di file privati, serve a creare file dummy di grandi dimensioni che riempiono lo spazio libero per rendere più difficile recuperare i file eliminati.

## Perchè?
Quando eliminiamo dei file, il filesystem marca quei settori di memoria come "liberi" ma non li sovrascrive, perciò per molto tempo quei file potrebbero essere ancora facilmente recuperabili.
Se un file occupa quegli spazi, i dati vengono effettivamente sovrascritti, perciò si rende il recupero con strumenti software molto più difficile o impossibile nella maggior parte dei casi.