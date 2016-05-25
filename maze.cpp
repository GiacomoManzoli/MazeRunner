#include "maze.h"
#include "block.h"
#include "tnt.h"

#include <iostream>

using namespace std;

Maze::Maze() : MAZE_HEIGHT(5), MAZE_WIDTH(5){
    // Caricamento delle texture
    bmps = new TextureBMP*[TEXTURE_COUNT];
    bmps[WALL_TEXTURE] = new TextureBMP("./assets/wall512.bmp");
    bmps[FLOOR_TEXTURE] = new TextureBMP("./assets/floor512.bmp");
    bmps[CEILING_TEXTURE] = new TextureBMP("./assets/ceiling512.bmp");
    bmps[TNT_TOP_TEXTURE] = new TextureBMP("./assets/tnt_top512.bmp");
    bmps[TNT_LATERAL_TEXTURE] = new TextureBMP("./assets/tnt_lato512.bmp");
    
    textures = new GLuint[TEXTURE_COUNT];
    glGenTextures(TEXTURE_COUNT, textures); // Crea i nomi per le texture
    
    loadTexture(textures[WALL_TEXTURE], bmps[WALL_TEXTURE]);
    loadTexture(textures[FLOOR_TEXTURE], bmps[FLOOR_TEXTURE]);
    loadTexture(textures[CEILING_TEXTURE], bmps[CEILING_TEXTURE]);
    loadTexture(textures[TNT_TOP_TEXTURE], bmps[TNT_TOP_TEXTURE]);
    loadTexture(textures[TNT_LATERAL_TEXTURE], bmps[TNT_LATERAL_TEXTURE]);

    // Allocazione della memoria e costruzione della mappa
    mazeMap = new int*[MAZE_HEIGHT];
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        mazeMap[i] = new int[MAZE_WIDTH];
    }
    // L'array deve andare nello heap, non posso fare il trick dell'inizializzazione, quindi le
    // dimensioni sono hard-coded ed è ancora nello stack
    int debug_maze_1[25] = {
        1,1,1,1,1, 
        1,0,0,2,1, 
        1,0,1,0,1, 
        1,2,0,2,1, 
        1,1,1,1,1
    };

    cout << MAZE_WIDTH <<endl;
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            mazeMap[i][j] = debug_maze_1[i*MAZE_HEIGHT +j];
            cout << mazeMap[i][j];
        }
        cout << endl;
    }
    // Allocazione della memoria e costruzione dei blocchi
    mazeElements = new MazeObject**[MAZE_HEIGHT];
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        mazeElements[i] = new MazeObject*[MAZE_WIDTH];
    }
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            if (mazeMap[i][j] == WALL_SPACE) { // 1: tipo muro
                mazeElements[i][j] = new Block(i,j, textures[WALL_TEXTURE]);
            } else if (mazeMap[i][j] == TNT_SPACE) { // 2: tipo TNT
                mazeElements[i][j] = new TNT(i,j, textures[TNT_TOP_TEXTURE], textures[TNT_LATERAL_TEXTURE]);
            } else {
                mazeElements[i][j] = NULL;
            }
        }
    }
};

Maze::~Maze() {
    // Deallocazione della mappa
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        delete[] mazeMap[i];
    }
    delete[] mazeMap;

    // Deallocazione degli elementi della mappa
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            delete mazeElements[i][j];
        }
        delete[] mazeMap[i];
    }
    delete[] mazeElements;

    // Deallocazione delle texture
    for (int i = 0; i < TEXTURE_COUNT; ++i) {
        delete bmps[i];
    }
    delete[] bmps;
    delete[] textures;

};

/*
    Funzione che associa il file BMP ad una texture OpenGL
*/
void Maze::loadTexture(GLuint texture, TextureBMP* bmp){
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp->getWidth(), bmp->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, bmp->getData());
}

bool Maze::isWall(int x, int z) {
    if (z < 0 || z >= MAZE_HEIGHT || x < 0 || x >= MAZE_WIDTH) { //index out of bound
        /* I labirinti sono costruiti con tutto il muro in torno, quindi non dovrebbe mai
           verificarsi questo caso
        */
        return true;
    }
    cout <<"MAZE MAP[Z:"<<z<<"][X:"<<x<<"]:"<<mazeMap[z][x] <<endl;
    return mazeMap[z][x] == WALL_SPACE;
}

void Maze::draw() {
    glEnable( GL_TEXTURE_2D );
    // Disegna il paviemento
    /*
        Sia il pavimento che il soffitto vengono tracciati fino a MAZE_WIDTH-1, 
        ovvero dal centro del primo cubo, al centro dell'ultimo cubo, sia della
        riga che della colonna.

        glTexCord2f con un parametro > 1 ripete la stessa texture
    */
    glBindTexture(GL_TEXTURE_2D, textures[FLOOR_TEXTURE]);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);   
        glTexCoord2f(MAZE_WIDTH -1, 0);
        glVertex3f(MAZE_WIDTH -1, 0, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        
        glTexCoord2f(0, MAZE_HEIGHT -1);
        glVertex3f(0, 0, MAZE_HEIGHT -1);
        
        glTexCoord2f(MAZE_WIDTH -1, MAZE_HEIGHT-1);
        glVertex3f(MAZE_WIDTH -1, 0, MAZE_HEIGHT -1);
    glEnd();

    // Disegna i muri 
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            if (mazeElements[i][j] != NULL) { 
                mazeElements[i][j]->draw();
            } 
        }
    }

    // Disegna il soffitto
    glBindTexture(GL_TEXTURE_2D, textures[CEILING_TEXTURE]);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 1.0f, 0);
        
        glTexCoord2f(MAZE_WIDTH -1, 0);
        glVertex3f(MAZE_WIDTH -1, 1.0f, 0);
        
        glTexCoord2f(MAZE_WIDTH-1, MAZE_HEIGHT-1);
        glVertex3f(MAZE_WIDTH -1, 1.0f, MAZE_HEIGHT -1);
        
        glTexCoord2f(0, MAZE_HEIGHT-1);
        glVertex3f(0, 1.0f, MAZE_HEIGHT -1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable( GL_TEXTURE_2D );
};