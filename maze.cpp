#include "maze.h"
#include "block.h"
#include "tnt.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h> 
#include <stdlib.h>

using namespace std;

Maze::Maze() : MAZE_HEIGHT(5), MAZE_WIDTH(5){


    maze_height_ext=MAZE_HEIGHT;
    maze_width_ext=MAZE_WIDTH;
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
    tntCount = 3;
    activeTntCount = tntCount;
    mazeTime = 15;
    mazeObserverX = 1;
    mazeObserverZ = 1;
    mazeObserverA = -90;

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
    //for (int i = 0; i < MAZE_HEIGHT; i++) {
    for (int i = 0; i < maze_height_ext; i++) {
        delete[] mazeMap[i];
    }
    delete[] mazeMap;

    // Deallocazione degli elementi della mappa
    //for (int i = 0; i < MAZE_HEIGHT; i++) {
    for (int i = 0; i < maze_height_ext; i++) {
        //for (int j = 0; j < MAZE_WIDTH; j++) {
        for (int j = 0; j < maze_width_ext; j++) {
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

Maze::Maze(char path): MAZE_HEIGHT(5), MAZE_WIDTH(5) {


	//letture delle specifiche dal file ".txt"
	*local_path  = path;
	ifstream file(local_path);
	getline(file, righe, '\n');
    getline(file, colonne, '\n');
    getline(file, bombe, '\n');
    getline(file, pos_partenza, '\n');
    getline(file, inclinazione, '\n');
    getline(file, pos_uscita, '\n');
    maze_height_ext = atoi(righe.c_str());
    maze_width_ext = atoi(colonne.c_str());
    bombeInt = atoi(bombe.c_str());
    pos_partenzaInt = atoi(pos_partenza.c_str());
    inclinazioneInt = atoi(inclinazione.c_str());
    pos_uscitaInt = atoi(pos_uscita.c_str());
    int ind = 0;
    string matrice[maze_height_ext*maze_width_ext];
    for(int i=0; i<maze_height_ext; i++) {
        // legge la linea fino a che incontra il carattere '\n'
        getline(file, line, '\n');
        for(int j=0; j<maze_width_ext*2; j=j+2) {
            matrice[ind]=line[j];
            ind=ind+1;
        }
    }
    int debug_maze_1[maze_height_ext*maze_width_ext];
    for(int t=0; t<(maze_height_ext*maze_width_ext); t++) {
        //cout<<matrice[t]<<endl;
        int tem = atoi(matrice[t].c_str());
        debug_maze_1[t]=tem;
    }
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
    mazeMap = new int*[maze_height_ext];
    for (int i = 0; i < maze_height_ext; i++) {
        mazeMap[i] = new int[maze_width_ext];
    }
    // L'array deve andare nello heap, non posso fare il trick dell'inizializzazione, quindi le
    // dimensioni sono hard-coded ed è ancora nello stack

    tntCount = 3;
    activeTntCount = tntCount;
    mazeTime = 15;
    mazeObserverX = 1;
    mazeObserverZ = 1;
    mazeObserverA = -90;

    cout << maze_width_ext <<endl;
    for (int i = 0; i < maze_height_ext; i++) {
        for (int j = 0; j < maze_width_ext; j++) {
            mazeMap[i][j] = debug_maze_1[i*maze_height_ext +j];
            cout << mazeMap[i][j];
        }
        cout << endl;
    }
    // Allocazione della memoria e costruzione dei blocchi
    mazeElements = new MazeObject**[maze_height_ext];
    for (int i = 0; i < maze_height_ext; i++) {
        mazeElements[i] = new MazeObject*[maze_width_ext];
    }
    for (int i = 0; i < maze_height_ext; i++) {
        for (int j = 0; j < maze_width_ext; j++) {
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
    if (z < 0 || z >= maze_height_ext || x < 0 || x >= maze_width_ext) { //index out of bound
        /* I labirinti sono costruiti con tutto il muro in torno, quindi non dovrebbe mai
           verificarsi questo caso
        */
        return true;
    }
    cout <<"MAZE MAP[Z:"<<z<<"][X:"<<x<<"]:"<<mazeMap[z][x] <<endl;
    return mazeMap[z][x] == WALL_SPACE;
}

bool Maze::deactiveTnt(int x, int z) {
    if (z < 0 || z >= maze_height_ext || x < 0 || x >= maze_width_ext) { //index out of bound
        /* I labirinti sono costruiti con tutto il muro in torno, quindi non dovrebbe mai
           verificarsi questo caso
        */
        return false;
    }

    if (mazeMap[z][x] == TNT_SPACE){
        TNT* tnt = dynamic_cast<TNT*>(mazeElements[x][z]);
        if (tnt->deactive()) {
            activeTntCount--;
            return true;
        }
    } 
    return false;
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

     //materiale
    GLfloat ambiente[4] = { 1.0f, 1.0f, 1.0f, 1 };
    GLfloat direttiva[4] = { 1, 1, 1, 1 };
    GLfloat brillante[4] = { 1, 1, 1, 1 };
    
    //glMateriali(GL_FRONT, GL_SHININESS, 32);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
    

    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);   
        glTexCoord2f(maze_width_ext -1, 0);
        glVertex3f(maze_width_ext -1, 0, 0);
        
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        
        glTexCoord2f(0, maze_height_ext -1);
        glVertex3f(0, 0, maze_height_ext -1);
        
        glTexCoord2f(maze_width_ext -1, maze_height_ext-1);
        glVertex3f(maze_width_ext -1, 0, maze_height_ext -1);
    glEnd();

    GLfloat ambiente2[4] = { 0.2f,0.2f,0.2f,1 };
    GLfloat diffuse2[4] = { 0.8f,0.8f,0.8f,1 };
    GLfloat specular2[4] = { 0.0f,0.0f,0.0f,1 };
    //glMateriali(GL_FRONT, GL_SHININESS, 32);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
    // Disegna i muri 
    for (int i = 0; i < maze_height_ext; i++) {
        for (int j = 0; j < maze_width_ext; j++) {
            if (mazeElements[i][j] != NULL) { 
                mazeElements[i][j]->draw();
            } 
        }
    }

    // Disegna il soffitto
    glBindTexture(GL_TEXTURE_2D, textures[CEILING_TEXTURE]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 1.0f, 0);
        
        glTexCoord2f(maze_width_ext -1, 0);
        glVertex3f(maze_width_ext -1, 1.0f, 0);
        
        glTexCoord2f(maze_width_ext-1, maze_height_ext-1);
        glVertex3f(maze_width_ext -1, 1.0f, maze_height_ext -1);
        
        glTexCoord2f(0, maze_height_ext-1);
        glVertex3f(0, 1.0f, maze_height_ext -1);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable( GL_TEXTURE_2D );
};