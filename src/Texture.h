/**
 * @file    Texture.h
 * @brief
 * @author  Juan Guerrero Martín <j.guerrerom@alumnos.urjc.es>
 * @date    2016
 * @remarks Copyright (c) 2016 GMRV/URJC. All rights reserved.
 * Do not distribute without further notice.
 */

#ifndef TESSTECHS_TEXTURE_H_
#define TESSTECHS_TEXTURE_H_

#include <string>

namespace tesstechs
{
  class Texture
  {
  public:
    
    Texture( const char* fileName_ );

    virtual ~Texture( void );

    void initAsRGBA8ub( const char* fileName_ );

    unsigned char* loadTexture( const char* fileName_,
                                unsigned int &width_,
                                unsigned int &height_ );

    unsigned int getId();

  private:
    unsigned int _id;
  };

} /* namespace tesstechs */

#endif /* TESSTECHS_TEXTURE_H_ */