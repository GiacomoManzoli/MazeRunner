# MazeRunner

Mini-gioco realizzato da Giacomo Manzoli e Matteo Botticchia come progetto per il corso di Sistemi Multimediali - Laurea Magistrale in Informatica - Università degli Studi di Padova.

## Caratteristiche principali

- Generazione del labirinto a partire da un file di testo. La dimensione del labirinto può essere arbitrariamente grande, l'importante è che il file sia formattato come riportato successivamente.
- Controllo delle collisioni con gli ostacoli.
- Gestione del ridimensionamento della finestra per mantenere l'aspect ratio costante.
- Texture specifiche per i vari elementi
- Luce dinamica che simula una torcia
- **Minigioco**: l'osservatore compare in un punto preciso del labirinto e deve riuscire a disinnescare, passandoci sopra, tutte le bombe presenti entro il tempo limite.
- HUD che mostra il numero di bombe attive, il tempo rimasto e la direzione dell'osservatore.
- **Gestione dei suoni**: utilizzando OpenAL e FreeALUT vengono riprodotti dei suoni quando l'utente disinnesca una bomba e quando la partita si conclude. Inoltre, ogni bomba finché è attiva emette un suono spazializzato per rendere più facile individuarla.

## Compilazione ed esecuzione

```
$ make
$ ./a.out levels/level1.txt
```

Per poter compilare il progetto è necessario che siano presenti le librerie OpenGL/AL e FreeGLUT/ALUT ([http://stackoverflow.com/a/3927988](http://stackoverflow.com/a/3927988)).

Il progetto è stato testato su Ubuntu 15.10 e compilato con g++ 5.2.1.

Il Makefile e gli `#include` permettono di compilare ed eseguire il progetto anche su Mac OS X (10.11 g++ 4.2.1). 
Tuttavia, la versione di FreeALUT che viene installata su OS X utilizzando [Homebrew](http://brew.sh/) sembra avere dei problemi e non riproduce l'audio.

## Comandi

- `W`: avanti
- `S`: indietro
- `A`: spostamento a sinsitra
- `D`: spostamento a destra
- `Q`: rotazione a sinsitra
- `E`: rotazione a destra
- `Esc`: esci

## Classi

- **MazeObject**: classe astratta che rappresenta un elemento grafico che compare nel labiritino
- **Block**: posiziona un cubo di dimensioni 1.0fx1.0f a partire da un determinato punto. Il blocco in posizione (0,0) ha centro in (X: 0, Y:0.5, Z:0). Eredita da `MazeObject`.
- **TNT**: rappresenta una bomba da disinnescare. Eredita da `MazeObject`.
- **Maze**: contiene i blocchi che costituiscono il labirinto e le informazioni sulle bombe.
- **TextureBMP**: classe che rappresenta un immagine BMP dal utilizzare come texture
 

## Formato file 

Per il corretto funzionamento dell'applicazione è necessario che il file contente la descrizione del labirinto sia formattato secondo il seguente schema: 

```
(int) numero righe mappa
(int) numero colonne mappa
(int) numero bombe mappa
(int) tempo a disposizione espresso in secondi
(int) coordinata x osservatore
(int) coordinata z osservatore
(int) orientamento dell'osservatore espresso in gradi
descrizione mappa
```

E' inoltre richiesto che il **perimetro del labirinto sia un muro**.

Per la descrizione della mappa è necessario utilizzare la seguente codifica:

- `0`: cella vuota
- `1`: muro
- `2`: bomba

Ad esempio:

```
3
6
1
12
1
1
-90
1,1,1,1,1,1, 
1,0,0,0,2,1,
1,1,1,1,1,1
```

