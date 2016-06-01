#ifndef MAZE_H
#define MAZE_H

/*
    maze.h - Classe che rappresenta il labirinto

    Utilizzare più texture: http://stackoverflow.com/questions/5681948/multiple-textures-opengl-glut-c
*/

#if defined __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

using namespace std;

#include "maze_object.h"
#include "textureBMP.h"
#include <stdio.h> 
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#define EMPTY_SPACE 0
#define WALL_SPACE 1
#define TNT_SPACE 2
#define SPAWN_SPACE 3
#define EXIT_SPACE 4

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
    MazeObject*** mazeElements; // puntatore a puntatore a puntatore a Block (array bidimensionale di MazeObject*)
    const int MAZE_HEIGHT;
    const int MAZE_WIDTH;
    const int SETTINGS;
    GLuint* textures;
    TextureBMP** bmps;
    void loadTexture(GLuint texture, TextureBMP* bmp);
    int activeTntCount;
    int tntCount;
    int mazeTime;
    int mazeObserverX;
    int mazeObserverZ;
    int mazeObserverA;
    const char * path;
    const char * local_path;
    //string line;
    string righe;
    string colonne;
    string bombe;
    string pos_partenza;
    string inclinazione;
    string pos_uscita;
    int maze_height_ext;
    int maze_width_ext;
    int bombeInt;
    int pos_partenzaInt;
    int inclinazioneInt;
    int pos_uscitaInt;
    string matrice[maze_height_ext*maze_width_ext];
    int debug_maze_1[maze_height_ext*maze_width_ext];

public:
    Maze();
    ~Maze();
    Maze(char path);
    void draw();
    bool isWall(int x, int z);
    int getMazeTime() {return mazeTime;}; 
    int getTntCount() {return tntCount;};
    int getActiveTntCount() {return activeTntCount;};
    bool deactiveTnt(int x, int z); // Ritorna true se la tnt è stata disinnescata.
    int getMazeObeserverX() {return mazeObserverX;};
    int getMazeObeserverZ() {return mazeObserverZ;};
    int getMazeObeserverA() {return mazeObserverA;};
};

#endif