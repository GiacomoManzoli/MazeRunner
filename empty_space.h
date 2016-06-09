/*
    empty_space.h - Rappresenta un riquadro del labirinto in cui 
    l'osservatore può muoversi.
*/

#ifndef EMPTY_SPACE_H
#define EMPTY_SPACE_H

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

class EmptySpace : public MazeObject{
public:
    EmptySpace(int X, int Z, int floorTexture, int ceilTexture);
    virtual void draw();
private:
    int X;
    int Z;
    int floorTexture;
    int ceilTexture;
};

#endif