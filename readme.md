# MazeRunner

Esplorazione di un labirinto utilizzando OpenGL

## Compilazione ed esecuzione

```
$ make
$ ./a.out
```

# Classi

- **Block**: posiziona un cubo di dimensioni 1.0fx1.0f a partire da un determinato punto. Il blocco in posizione (0,0) ha centro in (X: 0, Y:0.5, Z:0).
- **Maze**: contiene i blocchi che costituiscono il labirinto e le informazioni sugli allarmi
- **TextureBMP**: classe che rappresenta un immagine BMP dal utilizzare come texture

# TODO

- Aggiustare Frustum
- Caricare labirinto da file
- Aggiungere suoni
- Aggiungere luce spotlight
- Aggiungere comandi moviemento camera
- Aggiungere controllo collisioni
- ...

# Altro

Codice formato labirinto:

- 0: cella vuota
- 1: muro
- 2: posizione persona
- 3: allarme



Info utili:

- le X crescono verso destra
- le Z crescono verso "in avanti"
- gli angoli sono espressi in gradi