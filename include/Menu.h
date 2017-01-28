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

#include "SDL.h"
//#include "SDL2_image/SDL_image.h"

#include "DisplayPiece.h"
//#include "Button.h"
#include "TextBox.h"
//#include "SelectionMenu.h"
//#include "SubMenu.h"

//-------------------------------------------------------------------------------------

class SubMenu;
class SelectionMenu;
class Button;

class Menu: virtual public DisplayPiece
{
 public:

  Menu(float screen_x, float screen_y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  Menu(float rel_x, float rel_y, float rel_w, float rel_h,  Menu * parent );
  virtual ~Menu();

  void addButton(Button * button);
  void addTextBox(TextBox * box);
  void addTextLine(TextLine * message);
  void addSubMenu(SubMenu * submenu);
  void addSelectionMenu(SelectionMenu * sl);
  void clear();
  bool collide(float pos_x, float pos_y);
  void makeCloseButton();
  virtual bool outcome();
  virtual void render(int cameraoffset_x, int cameraoffset_y, float zoom);
  void renderSubItems();
  using DisplayPiece::setActive;
  void setActive(bool b);
  virtual void setXYPositions(float x, float y);
  void wipe();

  Button * getButton(int e)
  {
    return mButtons[e];
  }
  TextBox * getTextBox(int e)
  {
    return mTextBoxes[e];
  }
  TextLine * getTextLine(int e)
  {
    return mTextLines[e];
  }
  SelectionMenu * getSelectionMenu(int sl)
  {
    return mSelectionMenus[sl];
  }
  int getSizeButtons()
  {
    return mButtons.size();
  }
  int getSizeTextLines()
  {
    return mTextLines.size();
  }
  int getSizeTextBoxes()
  {
    return mTextBoxes.size();
  }
  int getSizeSelectionMenus()
  {
    return mSelectionMenus.size();
  }
  int getSizeSubMenus()
  {
    return mSubMenus.size();
  }
  SubMenu * getSubMenu(int e)
  {
    return mSubMenus[e];
  }
  /*TextMaker * getTextMaker()
  {
    return mTextMaker;
    }*/

  //TextMaker * mTextMaker;

 protected:
  std::vector<Button*> mButtons;
  std::vector<SubMenu*> mSubMenus;
  std::vector<TextLine*> mTextLines;
  std::vector<TextBox*> mTextBoxes;
  std::vector<SelectionMenu*> mSelectionMenus;

 private:

};

ReturnContainer closeMenu(ArgContainer);
Menu * makeInfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textHandler);


#endif

