//Base class for all menus and sceen displays
//
//Kevin Maguire
//28/03/2016
//

//-------------------------------------------------------------------------------------

#ifndef DISPLAYPIECE_H_
#define DISPLAYPIECE_H_

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "TextMaker.h"

//-------------------------------------------------------------------------------------

class DisplayPiece
{
 public:
  
  DisplayPiece(float screen_x, float screen_y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler);
  DisplayPiece(float rel_x, float rel_y, float rel_w, float rel_h, DisplayPiece * parent);
  //DisplayPiece();
  virtual ~DisplayPiece();

  void loadImage(std::string filename);
  virtual void setActive(bool b);
  void setPositions();
  

  virtual float getHeight()
  {
    return mHeight;
  }  
  virtual float getPosX() const
  {
    return mPos_x;
  }
  virtual float getPosY() const
  {
    return mPos_y;
  }
  virtual float getWidth()
  {
    return mWidth;
  }
  bool isActive()
  {
    return mActive;
  }
  virtual void setHeight(float h)
  {
    mHeight = h;
    mRect->h = h;
  }
  virtual void setPosX(float posx)
  {
    mPos_x = posx;
  }
  virtual void setPosY(float posy)
  {
    mPos_y = posy;
  }
  TextMaker * getTextMaker()
  {
    return mTextMaker;
  }
  virtual void setWidth(float w)
  {
    mWidth = w;
    mRect->w = w;
  }

  //relative functions
  DisplayPiece * getParent()
  {
    return mParent;
  }
  float getRelHeight()
  {
    return mRelHeight;
  }
  float getRelWidth()
  {
    return mRelWidth;
  }
  float getRelX()
  {
    return mRel_x;
  }
  float getRelY()
  {
    return mRel_y;
  }
  void setParent(DisplayPiece * parent)
  {
    mParent = parent;
  }
  void setRelHeight(float rh)
  {
    mRelHeight = rh;
  }
  void setRelWidth(float rw)
  {
    mRelWidth = rw;
  }
  void setRelX(float rx)
  {
    mRel_x = rx;
  }
  void setRelY(float ry)
  {
    mRel_y = ry;
  }
  
  SDL_Texture *mTexture;
  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;
  TextMaker * mTextMaker;
  SDL_Rect * mRect;

 protected:
  bool mActive;  
  
 private:
  float mPos_x;
  float mPos_y;
  float mWidth;
  float mHeight;
  
  //relative members
  float mRel_x;
  float mRel_y;
  float mRelWidth;
  float mRelHeight;
  DisplayPiece * mParent = nullptr;

};

#endif

