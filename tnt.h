#ifndef TNT_H
#define TNT_H

#if defined __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
    #include "/usr/local/Cellar/freealut/1.1.0/include/AL/alut.h"
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
    #include <AL/al.h>
    #include <AL/alc.h>
    #include <AL/alut.h>
#endif

#include "empty_space.h"

class TNT: public EmptySpace {
public:
    // topTexture e lateralTextur sono i nomi OpenGL delle texture da usare.
    // In questo modo le texture da usare vengono decise dal labirinto.
    // Inoltre, le texture vengono caricate una sola volta e vanno bene per tutti
    // gli oggetti di questo tipo.
    TNT(int X, int Z, int floorTexture, int ceilTexture, int topTexture, int lateralTexture, ALuint buffer);
    ~TNT();
    virtual void draw();
    bool deactive(); // ritorna true se la tnt è viene disattivata, false se è già stata disattivata
    void stopSound();
private:
    int X;
    int Z;
    int topTexture;
    int lateralTexture;
    bool active;
    ALuint audioSource;
};

#endif