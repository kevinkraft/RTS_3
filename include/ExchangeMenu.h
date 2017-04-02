//Menu for setting up an Exchange
//
//Kevin Maguire
//23/03/2017
//

//Add:
// * Need two selection sub menus
//   * one for the acter items, and one for the target items
//   * When a selection menu button is pressed the item becomes the active item
// * Need a way to input item amount
//   * use a textbox that shows the number and buttons to increase decrease the value

//Potential Problem:
// * What if the inventory changes while the menu is up?
//   * You could put a lock on both inventories when the menu is up
//     * set exchange so that it waits if ItemGroup is "locked"

//-------------------------------------------------------------------------------------

#ifndef EXCHANGEMENU_H_
#define EXCHANGEMENU_H_

//#include <string>
//#include <iostream>

//#include "Button.h"
//#include "Map.h"
//#include "EntityAction.h"
#include "Menu.h"
//#include "Resource.h"
//#include "TextMaker.h"
#include "Unit.h"

//-------------------------------------------------------------------------------------

class ExchangeMenu: public Menu
{
 public:

  ExchangeMenu(float x, float y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  ExchangeMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  virtual ~ExchangeMenu();

  std::vector< std::pair<int, float> > getFinalExchangeList();
  void clear();
  void makeCloseButton();
  void populate(Unit * acter, EntityAction * target);
  bool outcome();
  void updateSelectedItems();
  void wipe();

  Unit * getActer()
  {
    return mActer;
  }
  std::vector< std::pair<int,float> > getExchangeList()
  {
    return mExchangeList;
  }
  bool getFinishedSelection()
  {
    return mFinishedSelection;
  }
  EntityAction * getTarget()
  {
    return mTarget;
  }
  bool getWasClosed()
  {
    return mWasClosed;
  }
  void setActer(Unit * u)
  {
    mActer = u;
  }
  void setExchangeList(std::vector< std::pair<int,float> > ex)
  {
    mExchangeList = ex;
  }
  void setFinishedSelection(bool b)
  {
    mFinishedSelection = b;
  }
  void setTarget(EntityAction * ea)
  {
    mTarget = ea;
  }
  void setWasClosed(bool b)
  {
    mWasClosed = b;
  }

 private:

  void setup();

  Unit * mActer = nullptr;
  EntityAction * mTarget = nullptr;
  std::vector< std::pair<int,float> > mExchangeList;
  Item * mSelectedItem;
  bool mFinishedSelection;
  bool mWasClosed;

};

ReturnContainer cancelPreviousEntry(ArgContainer args);
ReturnContainer setExchangeMenuSelection(ArgContainer args);
ReturnContainer closeExchangeMenu(ArgContainer);

#endif
