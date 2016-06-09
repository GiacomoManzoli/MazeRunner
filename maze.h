#ifndef MAZE_H
#define MAZE_H

/*
    maze.h - Classe che rappresenta il labirinto

    Utilizzare più texture: http://stackoverflow.com/questions/5681948/multiple-textures-opengl-glut-c
*/

// Inclusione di OpenGL/GLUT/ALUT cross platform
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

#include "maze_object.h"
#include "textureBMP.h"
#include "tnt.h"
#include <stdio.h> 
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

// Codici mappa
#define EMPTY_SPACE 0
#define WALL_SPACE 1
#define TNT_SPACE 2

// Id delle texture per OpenGL
#define WALL_TEXTURE 0
#define FLOOR_TEXTURE 1
#define CEILING_TEXTURE 2
#define TNT_LATERAL_TEXTURE 3
#define TNT_TOP_TEXTURE 4

#define TEXTURE_COUNT 5

class Maze
{
private:
    int** mazeMap; // puntatore a puntatore ad interi (array bidimensionale di interi)
    MazeObject*** mazeElements; // puntatore a puntatore a puntatore a MazeElements (array bidimensionale di MazeObject*)
    TNT** tnts; // Array di TNT, serve per disattivare i suoni delle tnt quando finisce la partita
    GLuint* textures;
    TextureBMP** bmps;
    void loadTexture(GLuint texture, TextureBMP* bmp);
    int activeTntCount;
    int tntCount;
    int mazeTime;
    int maze_height_ext;
    int maze_width_ext;
    int mazeObserverX;
    int mazeObserverZ;
    int mazeObserverA;
    ALuint tntAudioBuffer;

    
public:
    Maze();
    ~Maze();
    Maze(const char * path);
    void draw();
    bool isWall(int x, int z);
    int getMazeTime() {return mazeTime;}; 
    int getTntCount() {return tntCount;};
    int getActiveTntCount() {return activeTntCount;};
    bool deactiveTnt(int x, int z); // Ritorna true se la tnt è stata disinnescata.
    int getMazeObeserverX() {return mazeObserverX;};
    int getMazeObeserverZ() {return mazeObserverZ;};
    int getMazeObeserverA() {return mazeObserverA;};
    void stopSounds();
};

#endif