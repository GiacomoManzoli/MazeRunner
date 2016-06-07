#include "empty_space.h"

#include <iostream>

using namespace std;

EmptySpace::EmptySpace(int XX, int ZZ, int ft, int ct){
    //cout <<"Costruito blocco in "<<X << " " <<Z <<endl;
    X = XX;
    Z = ZZ;
    floorTexture = ft;
    ceilTexture = ct;
}


void EmptySpace::draw() {
    cout << "Drawing " <<X <<" " <<Z <<endl;
    GLfloat ambient[4] = { 0.2f, 0.2f, 0.2f, 1 };
    GLfloat diffuse[4] = { 0.7f, 0.7f, 0.7f, 1 };
    GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    glBindTexture(GL_TEXTURE_2D, ceilTexture);
    glBegin(GL_QUADS);
   
    // i vertici sono dati in senso orario per avere le facce principali
    // rivolte verso l'interno.
    // Faccia sopra
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(1, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    
    
    
    glEnd();

    glBindTexture(GL_TEXTURE_2D, floorTexture);
    glBegin(GL_QUADS);
    //Faccia sotto
    glNormal3f(0, 1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(1, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glEnd();
}