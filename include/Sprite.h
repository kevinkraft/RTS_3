#ifndef SPRITE_H_
#define SPRITE_H_


#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "global.h"
#include "texture.h"


class Sprite
{
 public:
  
  Sprite(std::string filename, float x, float y, SDL_Renderer *renderer, SDL_Window *window, float scale=TILE_SIZE);
  Sprite(float x, float y, float scale=TILE_SIZE);
  virtual ~Sprite();

  bool collide(float x, float y, float xtol, float ytol, int cameraoffset_x, int cameraoffset_y, float zoom);
  //float getPixelX(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  //float getPixelY(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  float getZOrder();
  void loadImage();
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0, int height=0.);
  
  std::string getFilename()
    {
      return mFilename;
    }  
  float getPosX() const
  {
    return mPos_x;
  }
  float getPosY() const
  {
    return mPos_y;
  }
  float getScale()
  {
    return mScale;
  }
  void setFilename(std::string filename)
  {
    mFilename = filename;
  }
  void setPosX(float posx)
  {
    mPos_x = posx;
  }
  void setPosY(float posy)
  {
    mPos_y = posy;
  }
  void setScale(float scale)
  {
    mScale = scale;
  }
  
  SDL_Texture *mTexture;
  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;
  SDL_Rect *mRect;
  
 private:
  float mPos_x;
  float mPos_y;
  std::string mFilename;



  float mScale;

};

#endif
