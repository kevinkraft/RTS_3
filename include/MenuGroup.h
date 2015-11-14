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
  Menu * collide(float pos_x, float pos_y, float cameraoffset_x, float cameraoffset_y, float zoom);
  bool isActive();
  void setAllNotActive();
  void removeMenu(Menu * menu);  
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  
  std::vector<Menu*> menus;
    
};

#endif 
