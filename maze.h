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

#include "maze_object.h"
#include "textureBMP.h"

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
    GLuint* textures;
    TextureBMP** bmps;
    void loadTexture(GLuint texture, TextureBMP* bmp);
    int activeTntCount;
    int tntCount;
    int mazeTime;
public:
    Maze();
    ~Maze();
    void draw();
    bool isWall(int x, int z);
    int getMazeTime() {return mazeTime;}; 
    int getTntCount() {return tntCount;};
    int getActiveTntCount() {return activeTntCount;};
    bool deactiveTnt(int x, int z); // Ritorna true se la tnt è stata disinnescata.
};

#endif