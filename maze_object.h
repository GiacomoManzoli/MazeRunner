/*
	maze_object.h - Classe astratta che rappresenta un elemento del labirinto
	che può essere renderizzato
*/
#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

class MazeObject {
public:
    virtual ~MazeObject() {}
    virtual void draw() = 0;
};

#endif