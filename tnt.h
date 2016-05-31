#ifndef TNT_H
#define TNT_H

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

class TNT: public MazeObject {
public:
    // topTexture e lateralTextur sono i nomi OpenGL delle texture da usare.
    // In questo modo le texture da usare vengono decise dal labirinto.
    // Inoltre, le texture vengono caricate una sola volta e vanno bene per tutti
    // gli oggetti di questo tipo.
    TNT(int X, int Z, int topTexture, int lateralTexture);
    ~TNT();
    virtual void draw();
    bool deactive(); // ritorna true se la tnt è viene disattivata, false se è già stata disattivata
private:
    int X;
    int Z;
    int topTexture;
    int lateralTexture;
    bool active;
};

#endif