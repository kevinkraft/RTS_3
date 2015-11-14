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
  bool isActive();
  void setAllNotActive();
  void removeMenu(Menu * menu);  
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  
  std::vector<Menu*> menus;
    
};

#endif 
