/* Although the original version of the code that was used
 * didn't include a header, it's just fair that, just like
 * the corresponding C file, this header file be not under
 * any kind of license.*/

#ifndef _TEXLOADER_H_
#define _TEXLOADER_H_

#include <stdio.h>
#include <GL/glut.h>

#define MAX_NO_TEXTURES 338

typedef struct BMPImagem 
{
    int width;
    int height;
    char * data;
} BMPImage;

extern GLuint texture_id[MAX_NO_TEXTURES];

void getBitmapImageData(char * pFileName, BMPImage * pImage);
void loadTextures();
void initTexture();

#endif
