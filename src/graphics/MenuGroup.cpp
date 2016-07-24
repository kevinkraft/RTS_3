#include "MenuGroup.h"
#include "EntityAction.h"
#include "PopMenu.h"

MenuGroup::MenuGroup()
{}

MenuGroup::~MenuGroup()
{
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      delete (*it);
    }
}

void MenuGroup::addMenu(Menu* menu)
{
  menus.push_back(menu);
}

/*Menu * MenuGroup::getPopMenu()
{
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      if ( dynamic_cast<PopMenu*>((*it)) != NULL)
	{
	  return (*it);
	}
    }      
  std::cout << "MenuGroup::getPopMenu: WARN: The MenuGroup doesn't contain a pop menu" << std::endl;
  return nullptr;
  }*/

Menu * MenuGroup::collide(float x, float y)
{
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      if ( (*it)->collide(x, y) == true )
	{
	  return (*it);
	}
    }
  return nullptr;
}

bool MenuGroup::isActive()
{
  //check if any menus are active
  bool active = false;
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      if ( (*it)->isActive() )
	{
	  active = true;
	}
    }      
  return active;
}

void MenuGroup::setAllNotActive()
{
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      (*it)->setActive(false);
    }      
}

void MenuGroup::removeMenu(Menu* menu)
{
  menus.erase(std::remove(menus.begin(), menus.end(), menu), menus.end());
}

void MenuGroup::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  for(std::vector<Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
    {
      //std::cout << "INFO: MenuGroup::render: Is Menu active? " << (*it)->isActive() << std::endl;
      //std::cout << "INFO: MenuGroup::render:  (*it)->getPosX(): " << (*it)->getPosX() << std::endl;
      //std::cout << "INFO: MenuGroup::render:  (*it)->getPosY(): " << (*it)->getPosY() << std::endl;
      //std::cout << "INFO: MenuGroup::render:  (*it)->getHeight(): " << (*it)->getHeight() << std::endl;
      //std::cout << "INFO: MenuGroup::render:  (*it)->getWidth(): " << (*it)->getWidth() << std::endl;
      (*it)->render(cameraoffset_x, cameraoffset_y, zoom);
    }    
}
