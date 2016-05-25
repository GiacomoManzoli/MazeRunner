#include "block.h"

#include <iostream>

using namespace std;

Block::Block(int XX, int ZZ, int wt){
    //cout <<"Costruito blocco in "<<X << " " <<Z <<endl;
    X = XX;
    Z = ZZ;
    wallTexture = wt;
}


void Block::draw() {
    //cout << "Drawing " <<X <<" " <<Z <<endl;
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    
    glNormal3f(0, 0, 1);
    glTexCoord2f(1, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    
    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    
    glNormal3f(1, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    
    glNormal3f(-1, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    
    // Faccia sopra
    glNormal3f(0, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 2*HALF_BLOCK_SIZE, Z+HALF_BLOCK_SIZE);
    
    //Faccia sotto
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 1);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z-HALF_BLOCK_SIZE);
    glTexCoord2f(0, 0);
    glVertex3f(X+HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    glTexCoord2f(1, 0);
    glVertex3f(X-HALF_BLOCK_SIZE, 0, Z+HALF_BLOCK_SIZE);
    
    glEnd();
}