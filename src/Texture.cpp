

/**
 * @file    Texture.cpp
 * @brief
 * @author  Juan Guerrero Martín <j.guerrerom@alumnos.urjc.es>
 * @date    2016
 * @remarks Copyright (c) 2016 GMRV/URJC. All rights reserved.
 * Do not distribute without further notice.
 */

#include "Texture.h"

// Image processing.
#include <FreeImage.h>

#include <iostream>
#include <fstream>
#include <string>
//#include <sstream>
#include <iterator>
#include <vector>
#include <cstring>

#include <GL/glew.h>
#ifdef Darwin
#include <gl.h>
#include <glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace tesstechs
{

  Texture::Texture( const char* fileName_ )
  {
    initAsRGBA8ub( fileName_ );
  }

  Texture::~Texture( void )
  {
    glDeleteTextures(1, &_id);
  }

  void Texture::initAsRGBA8ub( const char* fileName_ )
  {
    unsigned char *map;
    unsigned int w, h;
    map = loadTexture(fileName_, w, h);
    if (!map)
    {
      std::cout << "Error cargando el fichero: " << fileName_ << std::endl;
      exit(-1);
    }

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)map);

    delete[] map;

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  }

  unsigned char* Texture::loadTexture( const char* fileName_,
                                       unsigned int &width_,
                                       unsigned int &height_ )
  {
    FreeImage_Initialise(TRUE);

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fileName_, 0);
    if (format == FIF_UNKNOWN)
      format = FreeImage_GetFIFFromFilename(fileName_);
    if ((format == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(format))
      return NULL;

    FIBITMAP* img = FreeImage_Load(format, fileName_);
    if (img == NULL)
      return NULL;

    FIBITMAP* tempImg = img;
    img = FreeImage_ConvertTo32Bits(img);
    FreeImage_Unload(tempImg);

    width_ = FreeImage_GetWidth(img);
    height_ = FreeImage_GetHeight(img);

    //BGRA a RGBA
    unsigned char * map = new unsigned char[4 * width_*height_];
    char *buff = (char*)FreeImage_GetBits(img);

    for (unsigned int j = 0; j<width_*height_; j++){
      map[j * 4 + 0] = buff[j * 4 + 2];
      map[j * 4 + 1] = buff[j * 4 + 1];
      map[j * 4 + 2] = buff[j * 4 + 0];
      map[j * 4 + 3] = buff[j * 4 + 3];
    }

    FreeImage_Unload(img);
    FreeImage_DeInitialise();

    return map;
  }

  unsigned int Texture::getId()
  {
    return _id;
  }

} /* namespace tesstechs */

