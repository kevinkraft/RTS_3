//Class for selecting from a list of Selectables within a menu window
//
//Kevin Maguire
//21/08/2016
//

//Note:
// * x and y are screen positions
// * mSelection is the currently selected Selectable

//-------------------------------------------------------------------------------------

#ifndef SELECTIONMENU_H_
#define SELECTIONMENU_H_

#include <string>
#include <iostream>

#include "Selectable.h"
#include "SubMenu.h"
#include "ItemGroup.h"
#include "EntityGroup.h"

//-------------------------------------------------------------------------------------


class SelectionMenu: public SubMenu
{
 public:
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent);
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Selectable*> selection_list);
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Entity*> selection_list);
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, EntityGroup* eg);
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Item*> selection_list);
  SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, ItemGroup* ig);
  virtual ~SelectionMenu();

  void setup();

  // * outcome();
  /*  using SubMenu::render; 
      void render();*/

  Selectable * getSelectable(int s)
  {
    return mSelectionList[s];
  }  
  Selectable * getSelection()
  {
    return mSelection;
  }  
  void setSelection( int i )
  {
    mSelection = mSelectionList[i];
  }
  void setSelectionList(std::vector<Selectable*> sl)
  {
    mSelectionList = sl;
  }


 private:
  std::vector<Selectable*> mSelectionList;
  Selectable* mSelection;
};

  ReturnContainer setButtonSelection(ArgContainer args);


#endif

