/*
	textureBMP.h - Classe che rappresenta un'immagine BMP da utilizzare
	come texture
*/
#ifndef TEXTURE_BMP_H
#define TEXTURE_BMP_H

class TextureBMP
{
private:
    unsigned char * data;
    int width;
    int height;
public:
    TextureBMP(const char* imagePath);
    ~TextureBMP();
    unsigned char* getData();
    int getWidth();
    int getHeight();
};

#endif