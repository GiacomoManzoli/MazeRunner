#include "coin.h"

#include <iostream>
#include <math.h>

using namespace std;



Coin::Coin(int XX, int ZZ){
    //cout <<"Costruita moneta in "<<X << " " <<Z <<endl;
    X = XX;
    Z = ZZ;
}

Coin::~Coin(){
}

void Coin::draw() {
    
    float R = 0.15f;
    glPushMatrix();
    glTranslatef(X, R, Z);

    glBegin(GL_QUADS);
    
    //Faccia frontale
    glNormal3f(0, 0, 1);
    glTexCoord2f(1, 1);
    glVertex3f(R, R, R);
    glTexCoord2f(0, 1);
    glVertex3f(-R, R, R);
    glTexCoord2f(0, 0);
    glVertex3f(-R, -R, R);
    glTexCoord2f(1, 0);
    glVertex3f(R, -R, R);
    
    // Faccia posteriore
    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-R, R, -R);
    glTexCoord2f(0, 1);
    glVertex3f(R, R, -R);
    glTexCoord2f(0, 0);
    glVertex3f(R, -R, -R);
    glTexCoord2f(1, 0);
    glVertex3f(-R, -R, -R);
    
    //Faccia destra
    glNormal3f(1, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(R, R, -R);
    glTexCoord2f(0, 1);
    glVertex3f(R, R, R);
    glTexCoord2f(0, 0);
    glVertex3f(R, -R, R);
    glTexCoord2f(1, 0);
    glVertex3f(R, -R, -R);
    
    //Faccia Sinistra
    glNormal3f(-1, 0, 0);
    glTexCoord2f(1, 1);
    glVertex3f(-R, R, R);
    glTexCoord2f(0, 1);
    glVertex3f(-R, R, -R);
    glTexCoord2f(0, 0);
    glVertex3f(-R, -R, -R);
    glTexCoord2f(1, 0);
    glVertex3f(-R, -R, R);
    
    //Faccia sopra
    glNormal3f(0, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(R, R, -R);
    glTexCoord2f(0, 1);
    glVertex3f(-R, R, -R);
    glTexCoord2f(0, 0);
    glVertex3f(-R, R, R);
    glTexCoord2f(1, 0);
    glVertex3f(R, R, R);
    
    // Faccia sotto
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(-R, -R, -R);
    glTexCoord2f(0, 1);
    glVertex3f(R, -R, -R);
    glTexCoord2f(0, 0);
    glVertex3f(R, -R, R);
    glTexCoord2f(1, 0);
    glVertex3f(-R, -R, R);
    
    glEnd();
    glPopMatrix();
    /*
    Disegnare un cilindro ha vari problemi
    //cout << "Drawing " <<X <<" " <<Z <<endl;
    float H = 0.05f; // Metà dell'altezza del cilintro
    float R = 0.25f; // raggio del cilindro

    glPushMatrix();
    glTranslatef(X, 0.5f, Z);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    
    // Corpo del cilindro
    glBegin(GL_QUAD_STRIP);
        for(float t = 0;t < 6.283f;t += (6.283f / 64)) {
            glNormal3f(sin(t), 0, cos(t));
            glVertex3f(R * sin(t), H, R * cos(t));
            glNormal3f(sin(t), 0, cos(t));
            glVertex3f(R * sin(t), -H, R * cos(t));
        }
    glEnd(); 

    glBegin(GL_POLYGON);
    for(float a = 0;a < 6.283f;a += (6.283f / 128)) {
        glVertex3f(R*cos(a),0.5f, R*sin(a));
    }
    glEnd();
       
    glPopMatrix();*/
}