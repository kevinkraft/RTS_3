#include "texture.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Map.h"

#include "Menu.h"

#include "SubMenu.h"

//Note:
// * x and y are game coordinates
// * mRect is obsolete but may be needed for sub menus
// * You only need a new Menu child class if the outcomes of button pressed return
//   things that need further processing, like the actions in PopMenu

//Add:
// * When you add submenus and tabs lots of things will need to be added here

Menu::Menu(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
{
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTextMaker = textMaker;

  mRenderer = renderer;
  mWindow = window;
  
  mRect = new SDL_Rect();

  setPosX(x);
  setPosY(y);
  setWidth(w);
  setHeight(h);

  this->loadImage("res/images/menu/menu.png");

  setActive(false);
}

Menu::~Menu()
{
  std::cout << "Deleting Menu" << std::endl;
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<Message*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
}

void Menu::addButton(Button * button)
{
  mButtons.push_back(button);
}

void Menu::addMessage(Message * message)
{
  mMessages.push_back(message);
}

void Menu::addSubMenu(SubMenu * submenu)
{
  mSubMenus.push_back(submenu);
}

void Menu::clear()
{
  setActive(false);
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      delete (*it);
    }
  mSubMenus.clear();
  for(std::vector<Message*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
    {
      delete (*it);
    }
  mMessages.clear();
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
  mButtons.clear();
}

bool Menu::collide(float x, float y)
{
  //checks if a button is pressed or if the menu is clicked in
  //x and y in screen pos
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      if ( (*it)->collide(x, y, this) == true)
	{
	  return true;
	}
    }
  //check if menu is clicked in
  return pointInSquare(x, y, mPos_x, mPos_y, mWidth, mHeight);
}

void Menu::loadImage(std::string filename)
{
  mTexture = loadTexture(filename, mRenderer, true);
}

void Menu::makeCloseButton()
{
  //add a close button to the list of buttons on the menu
  float close_scale = 13./14.;
  FunctionCaller closeFunc = &closeMenu;
  ArgContainer ac;
  ac.setMenu(this);
  Button * closeInfoMenu = new Button( close_scale * getWidth() , 0., 1-close_scale, 1-close_scale, "X", closeFunc, ac, this );
  addButton(closeInfoMenu);
}

bool Menu::outcome()
{
  //returns true if we are done with the menu, fals otherwise
  if (mButtons.size() != 0)
    {
      ReturnContainer funcReturn;
      for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
	{
	  if ( (*it)->isPressed() )
	    {
	      //these default functions dont need anything done on the returns
	      funcReturn = (*it)->outcome();
	      break;
	    }
	}
    }
  return false;
}

void Menu::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if (mActive)
    {
      float rectposx = mPos_x;
      float rectposy = mPos_y;
      renderTexture(mTexture, mRenderer, rectposx, rectposy, mWidth, mHeight);
      renderSubItems();
    }
}

void Menu::renderSubItems()
{
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      (*it)->render();
    }
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      (*it)->render(this);
    }
  for(std::vector<Message*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
    {
      (*it)->render();
    }
}

void Menu::setActive(bool b)
  {
    mActive = b;
    if ( getSizeSubMenus() != 0 )
      {
	for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
	  {
	    (*it)->setActive(b);
	  }
      }
    if ( getSizeMessages() != 0 )
      {
	for(std::vector<Message*>::iterator it = mMessages.begin(); it != mMessages.end(); ++it)
	  {
	    (*it)->setActive(b);
	  }
      }
  }

void Menu::setPositions(float x, float y)
{
  //x and y are screen coords
  setPosX(x);
  setPosY(y);
}

//-------------------------------------------------------------------------------------
// Other functions
//-------------------------------------------------------------------------------------

ReturnContainer closeMenu(ArgContainer ac)
{
  std::cout << "Menu: closeMenu: INFO: In This Function" << std::endl;
  ac.mMenu->setActive(false);
  ReturnContainer rt;
  return rt;
}

Menu * makeInfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textHandler)
{
  //make the info menu
  Menu * info_menu = new Menu( 0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textHandler);
  //add a close button
  info_menu->makeCloseButton();
  //make a title
  Message * title = new Message(0., 0., 100., 100., "HELLO", textHandler);
  info_menu->addMessage(title);
  //make a stats menu
  std::cout << "Menu: makeInfoMenu: INFO: About To Make the Stat submenu" << std::endl;
  SubMenu * submenu_stats = new SubMenu(30., 125., 0.3, 0.75, info_menu);
  submenu_stats->setActive(true);
  info_menu->addSubMenu(submenu_stats);
  //make an inventory menu
  SubMenu * submenu_inv = new SubMenu(340., 125., 0.65, 0.75, info_menu);
  info_menu->addSubMenu(submenu_inv);
  submenu_inv->setActive(true);
  info_menu->setActive(true);
  std::cout << "Menu: makeInfoMenu: INFO: Returning the Info Menu to main" << std::endl;
  return info_menu;
}
