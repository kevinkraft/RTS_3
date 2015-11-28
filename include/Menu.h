//Base class for all menus
//
//Kevin Maguire
//12/08/2015
//

//Note:
// * x and y are screen positions

//-------------------------------------------------------------------------------------

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "TextMaker.h"

//#include "FunctionCaller.h"

#include "Button.h"
//#include "SubMenu.h"

//-------------------------------------------------------------------------------------

class SubMenu;
//class Button;

class Menu
{
 public:
  
  Menu(float screen_x, float screen_y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  virtual ~Menu();

  void addButton(Button * button);
  void addMessage(Message * message);
  void addSubMenu(SubMenu * submenu);
  void clear();
  bool collide(float pos_x, float pos_y);
  void loadImage(std::string filename);
  void makeCloseButton();
  virtual bool outcome();
  virtual void render(int cameraoffset_x, int cameraoffset_y, float zoom);
  void renderSubItems();
  void setActive(bool b);
  virtual void setPositions(float x, float y);
  
  Button * getButton(int e)
  {
    return mButtons[e];
  }  
  float getHeight()
  {
    return mHeight;
  }  
  Message * getMessage(int e)
  {
    return mMessages[e];
  }  
  float getPosX() const
  {
    return mPos_x;
  }
  float getPosY() const
  {
    return mPos_y;
  }
  int getSizeButtons()
  {
    return mButtons.size();
  }  
  int getSizeMessages()
  {
    return mMessages.size();
  }  
  int getSizeSubMenus()
  {
    return mSubMenus.size();
  }  
  SubMenu * getSubMenu(int e)
  {
    return mSubMenus[e];
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
  std::vector<SubMenu*> mSubMenus;
  std::vector<Message*> mMessages;
  
 private:
  float mPos_x;
  float mPos_y;

  float mWidth;
  float mHeight;

  SDL_Rect * mRect;
  bool mActive;
};

ReturnContainer closeMenu(ArgContainer);
Menu * makeInfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textHandler);


#endif

