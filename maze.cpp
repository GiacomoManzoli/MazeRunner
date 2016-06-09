#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h> 
#include <stdlib.h>

#include "maze.h"
#include "block.h"
#include "empty_space.h"
#include "tnt.h"

using namespace std;

Maze::Maze() : Maze("levels/debug.txt"){};

Maze::Maze(const char* path) {
    //
    // Caricamento delle texture
    //
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
    
    //
    // Caricamento dell'audio per le tnt
    //
    //string audioFile = "./assets/sounds/tnt-active.wav";      
    string audioFile = "./assets/sounds/sirentone_cut_mono.wav";
    tntAudioBuffer = alutCreateBufferFromFile(audioFile.c_str());

    //
    // Caricamento dei dati del file
    //
    string line, righe, colonne, bombe, inclinazione;

	ifstream file(path);

    // Dimensioni
    getline(file, righe, '\n');
    getline(file, colonne, '\n');
    maze_height_ext = atoi(righe.c_str());
    maze_width_ext = atoi(colonne.c_str());

    cout << "DIMENSIONI: RIGHE: " <<maze_height_ext << " COLONNE " <<maze_width_ext << endl;
    // TNT
    getline(file, bombe, '\n');
    tntCount = atoi(bombe.c_str());
    activeTntCount = tntCount;
    
    // Tempo
    string time_str;
    getline(file, time_str, '\n');
    mazeTime = atoi(time_str.c_str());
    
    // Posizione osservatore
    string pos_partenza_x;
    string pos_partenza_z;
    getline(file, pos_partenza_x, '\n');
    getline(file, pos_partenza_z, '\n');
    getline(file, inclinazione, '\n');
    mazeObserverX = atoi(pos_partenza_x.c_str());
    mazeObserverZ = atoi(pos_partenza_z.c_str());
    mazeObserverA = atoi(inclinazione.c_str());

    
    // Allocazione della memoria e costruzione per la mappa e i blocchi
    tnts = new TNT*[tntCount];
    mazeMap = new int*[maze_height_ext];
    mazeElements = new MazeObject**[maze_height_ext];
    for (int i = 0; i < maze_height_ext; i++) {
        mazeMap[i] = new int[maze_width_ext];
        mazeElements[i] = new MazeObject*[maze_width_ext];
    }
    //
    //  Lettura e costurzione della mappa
    //
    int ind = 0;
    cout << "MATRICE LETTA" <<endl;
    for(int i=0; i<maze_height_ext; i++) {
        // legge la linea fino a che incontra il carattere '\n'
        getline(file, line, '\n');
        for(int j=0; j<maze_width_ext*2; j=j+2) {
            cout << line[j];
            mazeMap[i][j/2] = ((int)line[j] - 48);
            ind=ind+1;
        }
        cout << endl;
    }
   

    //
    // Costruzione dei blocchi
    //
    int contr_TNT = 0;
    for (int i = 0; i < maze_height_ext; i++) { // z
        for (int j = 0; j < maze_width_ext; j++) { // x
            if (mazeMap[i][j] == WALL_SPACE) { // 1: tipo muro
                mazeElements[i][j] = new Block(j,i, textures[WALL_TEXTURE]);
                cout << "W";
            } else if (mazeMap[i][j] == TNT_SPACE) { // 2: tipo TNT
                mazeElements[i][j] = new TNT(j,i,textures[FLOOR_TEXTURE], textures[CEILING_TEXTURE], textures[TNT_TOP_TEXTURE], textures[TNT_LATERAL_TEXTURE], tntAudioBuffer);
                tnts[contr_TNT] = (TNT*)mazeElements[i][j];
                contr_TNT = contr_TNT + 1;
                cout << "T";
            } else {
                mazeElements[i][j] = new EmptySpace(j,i, textures[FLOOR_TEXTURE], textures[CEILING_TEXTURE]);
                cout << "E";
            }
        }
        cout << endl;
    }

    //  
    // Controlli sul file in input
    //
    if (contr_TNT != activeTntCount){
        cout << "ERROR: Numero di TNT errato!!!" <<endl;
        exit(0);
    }
};

Maze::~Maze() {
    // Deallocazione della mappa
    for (int i = 0; i < maze_height_ext; i++) {
        delete[] mazeMap[i];
    }
    delete[] mazeMap;

    // Deallocazione degli elementi della mappa
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
    delete[] tnts;
    alDeleteBuffers(1, &tntAudioBuffer);
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
        /* 
            I labirinti sono costruiti con tutto il muro in torno,
            quindi non dovrebbe mai verificarsi questo caso
        */
        return true;
    }
    //cout <<"MAZE MAP[Z:"<<z<<"][X:"<<x<<"]:"<<mazeMap[z][x] <<endl;
    return mazeMap[z][x] == WALL_SPACE;
}

bool Maze::deactiveTnt(int x, int z) {
    if (z < 0 || z >= maze_height_ext || x < 0 || x >= maze_width_ext) { //index out of bound
        /* 
            I labirinti sono costruiti con tutto il muro in torno, quindi non dovrebbe mai
            verificarsi questo caso
        */
        return false;
    }
    if (mazeMap[z][x] == TNT_SPACE){
        TNT* tnt = dynamic_cast<TNT*>(mazeElements[z][x]);
        if (tnt->deactive()) { // Se ritorna false la tnt è già stata disinnescata
            activeTntCount--;
            return true;
        }
    } 
    return false;
}

void Maze::stopSounds() {
    for (int i = 0; i < tntCount; i++){
        tnts[i]->stopSound();
    }
}

void Maze::draw() {
    glEnable( GL_TEXTURE_2D );
   
    // Disegna gli elementi del labirinto
    for (int i = 0; i < maze_height_ext; i++) {
        for (int j = 0; j < maze_width_ext; j++) {
            if (mazeElements[i][j] != NULL) { 
                mazeElements[i][j]->draw();
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable( GL_TEXTURE_2D );

};