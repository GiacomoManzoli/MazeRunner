#include "textureBMP.h"

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

TextureBMP::TextureBMP(const char* imagePath) {
    unsigned char header[54];
    unsigned int imageSize;   // = width*height*3

    // Apre il file
    FILE * file = fopen(imagePath,"rb");
    if (!file){printf("Immagine non trovata\n"); return;}
    if ( fread(header, 1, 54, file)!=54 ){ // Controlla che l'header sia di 54 byte
        printf("Header BMP errato\n");
        data = NULL;
        return;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Header BMP errato\n");
        data =  NULL;
        return;
    }
    // Informazioni dell'header
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    
    // Check dei parametri
    if (imageSize == 0) imageSize=width*height*3; 
    
    // Crea lo spazio in memoria
    data = new unsigned char [imageSize];

    //cout << "W: "<<width <<" H: "<<height <<" S: "<<imageSize<<endl;
    // Carica i dati dal file
    fread(data,1,imageSize,file);
    fclose(file);

    // I file BMP sono salvati con BGR anziché RBG, è necessario fare lo swap dei due canali
    for(int i = 0; i < width * height ; ++i)
    {
       int index = i*3;
       unsigned char B,R;
       B = data[index];
       R = data[index+2];
       data[index] = R;
       data[index+2] = B;
    }
};

TextureBMP::~TextureBMP() {
    delete[] data;
};

unsigned char* TextureBMP::getData() { return data; };

int TextureBMP::getWidth() { return width; };
int TextureBMP::getHeight() { return height; };