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
  Sprite(float x, float y, float click_w=UNIT_CLICK_WIDTH, float click_h=UNIT_CLICK_HEIGHT,
	 float click_offset_x=UNIT_CLICK_OFFSET_X, float click_offset_y=UNIT_CLICK_OFFSET_Y,
	 float scale=TILE_SIZE);
  virtual ~Sprite();

  bool collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom);
  //float getPixelX(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  //float getPixelY(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  float getZOrder();
  void loadImage();
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0, int height=0.);
  
  float getClickHeight()
    {
      return mClickHeight;
    }  
  float getClickWidth()
    {
      return mClickWidth;
    }  
  float getClickOffsetX()
    {
      return mClickOffset_x;
    }  
  float getClickOffsetY()
    {
      return mClickOffset_y;
    }  
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
  void setClickHeight(float h)
  {
    mClickHeight = h;
  }
  void setClickWidth(float w)
  {
    mClickWidth = w;
  }
  void setClickOffsetX(float x)
  {
    mClickOffset_x = x;
  }
  void setClickOffsetY(float y)
  {
    mClickOffset_y = y;
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

  float mClickWidth;
  float mClickHeight;
  float mClickOffset_x;
  float mClickOffset_y;


  float mScale;

};

#endif
