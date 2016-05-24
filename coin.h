#ifndef COIN_H
#define COIN_H

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

class Coin: public MazeObject {
public:
    Coin(int X, int Z);
    ~Coin();
    virtual void draw();
private:
    int X;
    int Z;
};

#endif