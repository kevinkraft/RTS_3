//Right click popup menu
//
//Kevin Maguire
//30/08/2015
//

//Note:
// * x and y are game positions

//-------------------------------------------------------------------------------------

#ifndef POPMENU_H_
#define POPMENU_H_

#include <string>
#include <iostream>

#include "Button.h"
#include "Map.h"
#include "EntityAction.h"
#include "Menu.h"
#include "TextMaker.h"

//-------------------------------------------------------------------------------------

//class Button;

class PopMenu: public Menu
{
 public:
  
  PopMenu(float x, float y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  PopMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  virtual ~PopMenu();

  bool outcome();
  void scaleHeight();
  using Menu::setPositions;
  void setPositions(float x, float y, float cameraoffset_x, float cameraoffset_y, float zoom);
  //needs its own render so it stays in the same place on the map
  using Menu::render;
  void render(int cameraoffset_x, int cameraoffset_y, float zoom);

  float getGamePosX()
  {
    return mGamePosX;
  }  
  float getGamePosY()
  {
    return mGamePosY;
  }    
  float getItemHeight()
  {
    return mItemHeight;
  }  
  float getItemWidth()
  {
    return mItemWidth;
  }  
  EntityAction * getSelectedEntity()
  {
    return mSelectedEntity;
  }  
  void setGamePosX(float x)
  {
    mGamePosX = x;
  }
  void setGamePosY(float y)
  {
    mGamePosY = y;
  }
  void setItemHeight(float h)
  {
    mItemHeight = h;
  }
  void setItemWidth(float w)
  {
    mItemWidth = w;
  }
  void setSelectedEntity(EntityAction * entity)
  {
    mSelectedEntity = entity;
  }
  
 private:

  float mItemHeight = POP_MENU_ITEM_HEIGHT;
  float mItemWidth = POP_MENU_ITEM_WIDTH;

  float mGamePosX;
  float mGamePosY;

  EntityAction * mSelectedEntity;
  
};

#endif
