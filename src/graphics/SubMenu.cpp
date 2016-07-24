//#include "Menu.h"
#include "SubMenu.h"
#include "texture.h"

SubMenu::SubMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent) 
  : DisplayPiece(parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent),
    Menu( rel_x, rel_y, rel_w, rel_h, parent )
{
  setParent(parent);
  setRelX(rel_x);
  setRelY(rel_y);
  setRelHeight(rel_h);
  setRelWidth(rel_w);
  setPositions();
}

SubMenu::~SubMenu()
{}

void SubMenu::render()
{
  if ( isActive() )
    {
      /*std::cout << "INFO: SubMenu::render: Rendering an active SubMenu " << std::endl;
      std::cout << "INFO: SubMenu::render: this->getPosX(): " << this->getPosX() << std::endl;
      std::cout << "INFO: SubMenu::render: this->getPosY(): " << this->getPosY() << std::endl;
      std::cout << "INFO: SubMenu::render: this->getWidth(): " << this->getWidth() << std::endl;
      std::cout << "INFO: SubMenu::render: this->getHeight(): " << this->getHeight() << std::endl;*/
      //render self relative to the parent and update self to actual coords
      setPositions();
      renderTexture(mTexture, mRenderer, getPosX(), getPosY(), getWidth(), getHeight() );
      //then render buttons and submenu
      renderSubItems();
    }
}
