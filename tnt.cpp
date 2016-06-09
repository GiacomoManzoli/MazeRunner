#include "tnt.h"

#include <iostream>
#include <math.h>
#include <string>

#include "textureBMP.h"

using namespace std;

TNT::TNT(int XX, int ZZ, int ft, int ct, int tt, int lt, ALuint audioBuffer) : EmptySpace(XX,ZZ,ft,ct){
    X = XX;
    Z = ZZ;
    lateralTexture = lt;
    topTexture = tt;
    active = true;

    // Configura e riproduce il suono
    alGenSources(1, &audioSource);
    alSourcei(audioSource, AL_BUFFER, audioBuffer);
    alSourcef(audioSource, AL_PITCH, 1.0f);
    alSourcef(audioSource, AL_GAIN, 1.0f);
    alSource3f(audioSource, AL_POSITION, X, 0, Z);
    alSource3f(audioSource, AL_VELOCITY, 0, 0, 0);
    alSourcei(audioSource, AL_LOOPING, AL_TRUE); 
  
    alSourcef(audioSource, AL_ROLLOFF_FACTOR, 3);//Velocità con cui si attenua
    alSourcef(audioSource, AL_REFERENCE_DISTANCE, 2); // Distanza entro la quale non c'è attenuazione
    alSourcef(audioSource, AL_MAX_DISTANCE, 5); // Massima distanza fino alla quale si sente il suono

    //cout << "Riproduco suono in " << X << " " << Z <<endl;
    alSourcePlay(audioSource);
}

TNT::~TNT(){
}

// ritorna true se la tnt è viene disattivata, false se è già stata disattivata
bool TNT::deactive() {
    if (active){
        active = false;
        stopSound();
        alDeleteSources(1, &audioSource);
        return true;
    }
    return false;
};

void TNT::stopSound() {
    ALint state;
    alGetSourcei(audioSource, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING) {
        alSourceStop(audioSource);
    }
}

void TNT::draw() {
    // Disegna lo spazio vuoto (soffitto e pavimento)
    EmptySpace::draw();

    // Se la tnt è stata disattivata non viene disegnata
    if (! active) {return;}
    float R = 0.15f;
    glPushMatrix();
    glTranslatef(X, R, Z);
    //materiale
    GLfloat ambient[4] = { 0.6f, 0.6f, 0.6f, 1 };
    GLfloat diffuse[4] = { 0.7f, 0.7f, 0.7f, 1 };
    GLfloat specular[4] = { 0.1f, 0.1f, 0.1f, 1 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    
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
    
    glPopMatrix();
}