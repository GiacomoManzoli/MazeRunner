# MazeRunner

Esplorazione di un labirinto utilizzando OpenGL

## Compilazione ed esecuzione

```
$ make
$ ./a.out levels/debug1.txt
```

## Comandi

- `W`: avanti
- `S`: indietro
- `A`: spostamento a sinsitra
- `D`: spostamento a destra
- `Q`: rotazione a sinsitra
- `E`: rotazione a destra
- `Esc`: esci

# Classi

- **MazeObject**: classe astratta che rappresenta un elemento grafico che compare nel labiritino
- **Block**: posiziona un cubo di dimensioni 1.0fx1.0f a partire da un determinato punto. Il blocco in posizione (0,0) ha centro in (X: 0, Y:0.5, Z:0). Eredita da `MazeObject`.
- **TNT**: rappresenta una bomba da disinnescare. Eredita da `MazeObject`.
- **Maze**: contiene i blocchi che costituiscono il labirinto e le informazioni sulle bombe.
- **TextureBMP**: classe che rappresenta un immagine BMP dal utilizzare come texture
 

# Formato file 

```
(int) #righe mappa
(int) #colonne mappa
(int) #bombe mappa
(int) tempo a disposizione
(int) coordinata x osservatore
(int) coordinata z osservatore
(int) verso visuale
descrizione mappa
```

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

# TODO

- Aggiungere suoni
- Correggere luce spotlight

# Altro

Codice formato labirinto:

- 0: cella vuota
- 1: muro
- 2: bomba

Info utili:

- le X crescono verso destra
- le Z crescono verso "in avanti"
- in OpenGL gli angoli sono espressi in gradi, la libreria math usa i radianti