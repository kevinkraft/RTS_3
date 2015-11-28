#ifndef MENUGROUP_H_
#define MENUGROUP_H_

#include <iostream>
#include <vector>

#include "Menu.h"
#include "PopMenu.h"

class MenuGroup
{
 public:
  MenuGroup();
  virtual ~MenuGroup();

  void addMenu(Menu * menu);
  //Menu * getPopMenu();
  Menu * collide(float pos_x, float pos_y);
  bool isActive();
  void setAllNotActive();
  void removeMenu(Menu * menu);  
  void render(int cameraoffset_x, int cameraoffset_y, float zoom);
  
  std::vector<Menu*> menus;
    
};

#endif 
