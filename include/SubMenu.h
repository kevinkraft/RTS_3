//Class for a menu with coords relative to a parent menu
//
//Kevin Maguire
//22/11/2015
//

//Note:
// * x and y are screen positions

//-------------------------------------------------------------------------------------

#ifndef SUBMENU_H_
#define SUBMENU_H_

#include <string>
#include <iostream>

#include "Menu.h"

//-------------------------------------------------------------------------------------

class SubMenu: public Menu
{
 public:
  
  SubMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent);
  virtual ~SubMenu();

  using Menu::render;
  void render();

  void setParent(Menu * parent)
  {
    mParent = parent;
  }
  void setRelHeight(float h)
  {
    mRelHeight = h;
  }
  void setRelWidth(float w)
  {
    mRelWidth = w;
  }
  void setRelX(float x)
  {
    mRel_x = x;
  }
  void setRelY(float y)
  {
    mRel_y = y;
  }
  Menu * getParent()
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

 private:

  float mRel_x;
  float mRel_y;
  float mRelWidth;
  float mRelHeight;

  Menu * mParent;

};



#endif

