#include "texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"

#include "Menu.h"

#include "SubMenu.h"
#include "SelectionMenu.h"

//Note:
// * x and y are game coordinates
// * mRect is obsolete but may be needed for sub menus
// * You only need a new Menu child class if the outcomes of button pressed return
//   things that need further processing, like the actions in PopMenu

//Add:
// * When you add submenus and tabs lots of things will need to be added here
// * Selection menu doesnt need its own list, it derives from SubMenu
//   * See NumberBox, they are added to the menu as just a SubMenu

Menu::Menu(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(x, y, w, h, renderer, window, textMaker)
{
}

Menu::Menu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent)
  : DisplayPiece(rel_x, rel_y, rel_w, rel_h, parent)
{
}

Menu::~Menu()
{
  std::cout << "Deleting Menu" << std::endl;
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<TextLine*>::iterator it = mTextLines.begin(); it != mTextLines.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
    {
      delete (*it);
    }
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    {
      delete (*it);
    }
}

void Menu::addButton(Button * button)
{
  button->setActive( isActive() );
  mButtons.push_back(button);
}

void Menu::addSelectionMenu(SelectionMenu * box)
{
  box->setActive( isActive() );
  mSelectionMenus.push_back(box);
}

void Menu::addTextBox(TextBox * box)
{
  box->setActive( isActive() );
  mTextBoxes.push_back(box);
}

void Menu::addTextLine(TextLine * message)
{
  message->setActive( isActive() );
  mTextLines.push_back(message);
}

void Menu::addSubMenu(SubMenu * submenu)
{
  submenu->setActive( isActive() );
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
  for(std::vector<TextLine*>::iterator it = mTextLines.begin(); it != mTextLines.end(); ++it)
    {
      delete (*it);
    }
  mTextLines.clear();
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
  mButtons.clear();
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
    {
      delete (*it);
    }
  mTextBoxes.clear();
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    {
      delete (*it);
    }
  mSelectionMenus.clear();
}

bool Menu::collide(float x, float y)
{
  //checks if a button is pressed or if the menu is clicked in
  //x and y in screen pos
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      if ( (*it)->collide(x, y) == true)
	{
	  return true;
	}
    }
  //check submenus
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      if ( (*it)->collide(x, y) == true)
	{
	  return true;
	}
    }
  //check text boxes
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
    {
      //if ( (*it)->collide(x, y, this) == true)
      if ( (*it)->collide(x, y) == true)
	{
	  return true;
	}
    }
  //check SelectionMenus
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    {
      if ( (*it)->collide(x, y) == true)
	{
	  return true;
	}
    }
  //check if menu is clicked in
  return pointInSquare(x, y, this->getPosX(), this->getPosY(), this->getWidth(), this->getHeight() );
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
  //returns true if we are done with the menu, false otherwise
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
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      (*it)->outcome();
    }
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
    {
      (*it)->outcome();
    }
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    {
      (*it)->outcome();
    }
  return false;
}

void Menu::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if ( this->isActive() )
    {
      float rectposx = this->getPosX();
      float rectposy = this->getPosY();
      /*std::cout << "INFO: Menu::render: this->getPosX(): " << this->getPosX() << std::endl;
      std::cout << "INFO: Menu::render: this->getPosY(): " << this->getPosY() << std::endl;
      std::cout << "INFO: Menu::render: this->getWidth(): " << this->getWidth() << std::endl;
      std::cout << "INFO: Menu::render: this->getHeight(): " << this->getHeight() << std::endl;*/
      renderTexture(mTexture, mRenderer, rectposx, rectposy, this->getWidth(), this->getHeight());
      renderSubItems();
    }
}

void Menu::renderSubItems()
{
  //std::cout << "Menu::render: INFO: In This Function" << std::endl;
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      (*it)->render();
    }
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      (*it)->render();
    }
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    {
      (*it)->render();
    }
  for(std::vector<TextLine*>::iterator it = mTextLines.begin(); it != mTextLines.end(); ++it)
    {
      (*it)->render();
    }
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
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
  if ( getSizeTextLines() != 0 )
    {
      for(std::vector<TextLine*>::iterator it = mTextLines.begin(); it != mTextLines.end(); ++it)
        {
          (*it)->setActive(b);
        }
    }
  if ( getSizeTextBoxes() != 0 )
    {
      for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
        {
          (*it)->setActive(b);
        }
    }
  if ( getSizeSelectionMenus() != 0 )
    {
      for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
        {
          (*it)->setActive(b);
        }
    }
}

void Menu::setXYPositions(float x, float y)
{
  //x and y are screen coords
  setPosX(x);
  setPosY(y);
}

void Menu::wipe()
{
  //this is like Menu::clear() but it doesn't delete the subparts, just clears the TextBoxes
  for(std::vector<SubMenu*>::iterator it = mSubMenus.begin(); it != mSubMenus.end(); ++it)
    {
      (*it)->wipe();
    }
  for(std::vector<TextLine*>::iterator it = mTextLines.begin(); it != mTextLines.end(); ++it)
    {
      (*it)->setText(" ");
    }
  /*  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
      }*/
  for(std::vector<TextBox*>::iterator it = mTextBoxes.begin(); it != mTextBoxes.end(); ++it)
    {
      (*it)->setWords(" ");
    }
}

//-------------------------------------------------------------------------------------
// Other functions
//-------------------------------------------------------------------------------------

ReturnContainer closeMenu(ArgContainer ac)
{
  ac.mMenu->setActive(false);
  ac.mMenu->wipe();
  ReturnContainer rt;
  return rt;
}

Menu * makeInfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textHandler)
{
  TerminalText::printTerminal("INFO: Menu: makeInfoMenu: In this function.");

  std::string splitline = "And to find out that he has to carry this saddness with him in his heart is simply soulcrushing. It is like pouring salt on the wound because it reminds you that this amazing actor has died too. She wheeled her wheel barrow through the streets broad and  narrow crying cockles and mussels alive alive o. 65 people were killed and 314 injured in a blast in Gulshan-e-Iqbal-long-name-very-long Park, in Iqbal Town area of Lahore. The sound of the blast was heard around 6:30 pm today, with rescue teams dispatched to the site. These include 23 ambulances and rescue vehicles. The Irish Times today claims it has reproduced a copy of the paper from 1916 but guess what, it has taken out a sentence";
  //make the info menu
  Menu * info_menu = new Menu( 0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textHandler);
  /*TextBox* main_box = new TextBox( info_menu->getPosX(), info_menu->getPosY()+30., info_menu->getWidth(), 100.,
				   splitline, textHandler, info_menu);
				   info_menu->addTextBox(main_box);*/

  //add a close button
  info_menu->makeCloseButton();
  //make a title
  //TextLine * title = new TextLine(0., 0., 100., 50., "HELLO", textHandler);
  //info_menu->addTextLine(title);
  /*TextBox* title_box = new TextBox( 0., 0., 1., 1., splitline, textHandler, info_menu);
    info_menu->addTextBox(title_box);*/
  /*TextBox* title_box = new TextBox( 0., 40., 1, 0.2, splitline, textHandler, info_menu);
    info_menu->addTextBox(title_box);*/
  //make a stats menu
  //SubMenu * submenu_stats = new SubMenu(.5, 115., 0.3, 0.75, info_menu);
  SubMenu * submenu_stats = new SubMenu(50, 150, 0.3, 0.68, info_menu);
  info_menu->addSubMenu(submenu_stats);
  TextBox* stat_box = new TextBox( 0., 0., 1., 1., splitline, textHandler, submenu_stats);
  submenu_stats->addTextBox(stat_box);
  //make an inventory menu
  SubMenu * submenu_inv = new SubMenu(380., 150., 0.60, 0.68, info_menu);
  info_menu->addSubMenu(submenu_inv);
  TextBox* inv_box = new TextBox( 0., 0., 1., 1., splitline, textHandler, submenu_inv);
  submenu_inv->addTextBox(inv_box);

  /*TextBox* inv_box = new TextBox( submenu_inv->getPosX(), submenu_inv->getPosY(), submenu_inv->getWidth(), submenu_inv->getHeight(),
				  splitline, textHandler, info_menu);
  submenu_inv->addTextBox(inv_box);
  submenu_inv->setActive(true);*/
  info_menu->setActive(false);
  return info_menu;
}
