#include "tnt.h"

#include <iostream>
#include <math.h>

#include "textureBMP.h"

using namespace std;



TNT::TNT(int XX, int ZZ, int tt, int lt){
    //cout <<"Costruita moneta in "<<X << " " <<Z <<endl;
    X = XX;
    Z = ZZ;
    lateralTexture = lt;
    topTexture = tt;
    active = true;
}

TNT::~TNT(){
}

// ritorna true se la tnt è viene disattivata, false se è già stata disattivata
bool TNT::deactive() {
    if (active){
        active = false;
        return true;
    }
    return false;
};

void TNT::draw() {
    // Se la tnt è stata disattivata non viene disegnata
    if (! active) {return;}
    float R = 0.15f;
    glPushMatrix();
    glTranslatef(X, R, Z);
         //materiale
    GLfloat ambiente[4] = { 1.0f, 1.0f, 1.0f, 1 };
    GLfloat direttiva[4] = { 1, 1, 1, 1 };
    GLfloat brillante[4] = { 1, 1, 1, 1 };
    
    //glMateriali(GL_FRONT, GL_SHININESS, 32);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
    
    glBindTexture(GL_TEXTURE_2D, lateralTexture);
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

    glBindTexture(GL_TEXTURE_2D, topTexture);
    glBegin(GL_QUADS);
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
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
           GLfloat ambiente2[4] = { 0.2f,0.2f,0.2f,1 };
    GLfloat diffuse2[4] = { 0.8f,0.8f,0.8f,1 };
    GLfloat specular2[4] = { 0.0f,0.0f,0.0f,1 };
    //glMateriali(GL_FRONT, GL_SHININESS, 32);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular2);
    
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