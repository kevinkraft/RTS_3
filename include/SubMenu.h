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
//#include "RelativeDisplayPiece.h"

//-------------------------------------------------------------------------------------

class SubMenu: public Menu
{
 public:
  
  SubMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent);
  virtual ~SubMenu();

  using Menu::render; 
  void render();

 private:


};



#endif

