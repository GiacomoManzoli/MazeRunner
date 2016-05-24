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

#define WALL_TEXTURE 0
#define FLOOR_TEXTURE 1
#define CEILING_TEXTURE 2
#define TEXTURE_COUNT 3

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
public:
    Maze();
    ~Maze();
    void draw();
};

#endif