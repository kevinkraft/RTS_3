//Base class for all menus
//
//Kevin Maguire
//12/08/2015
//

//Note:
// * x and y are game positions

//-------------------------------------------------------------------------------------

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "Button.h"
#include "TextMaker.h"

//-------------------------------------------------------------------------------------

class Button;

class Menu
{
 public:
  
  Menu(float x, float y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  virtual ~Menu();

  void addButton(Button * button);
  void clear();
  bool collide(float pos_x, float pos_y, float cameraoffset_x, float cameraoffset_y, float zoom);
  void loadImage(std::string filename);
  virtual void outcome();
  void render(int cameraoffset_x, int cameraoffset_y, float zoom);
  void setPositions(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom);
  
  Button * getButton(int e)
  {
    return mButtons[e];
  }  
  int getSizeButtons()
  {
    return mButtons.size();
  }  
  float getHeight()
  {
    return mHeight;
  }  
  float getPosX() const
  {
    return mPos_x;
  }
  float getPosY() const
  {
    return mPos_y;
  }
  TextMaker * getTextMaker()
  {
    return mTextMaker;
  }
  float getWidth()
  {
    return mWidth;
  }
  bool isActive()
  {
    return mActive;
  }
  void setActive(bool b)
  {
    mActive = b;
  }
  void setHeight(float h)
  {
    mHeight = h;
    mRect->h = h;
  }
  void setPosX(float posx)
  {
    mPos_x = posx;
  }
  void setPosY(float posy)
  {
    mPos_y = posy;
  }
  void setWidth(float w)
  {
    mWidth = w;
    mRect->w = w;
  }
  
  SDL_Texture *mTexture;
  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;
  TextMaker * mTextMaker;

 protected:
  std::vector<Button*> mButtons;
  
 private:
  float mPos_x;
  float mPos_y;
  float mWidth;
  float mHeight;

  SDL_Rect * mRect;
  bool mActive;
};

#endif
