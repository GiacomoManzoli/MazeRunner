/*
    block.h - Rappresenta un blocco che costituisce una parete del labirinto
*/

#ifndef BLOCK_H
#define BLOCK_H

#if defined __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

#include "maze_object.h"

#define HALF_BLOCK_SIZE 0.5f // Metà della dimensione di un blocco
/*
    Il blocco ha come centro le coordinate X,Z specificate. La Y della parte bassa è 0, mentre la parte alta è 2*HALF_BLOCK_SIZE
*/

class Block : public MazeObject{
public:
    Block(int X, int Z);
    virtual void draw();
private:
    int X;
    int Z;
};

#endif