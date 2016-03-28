//#include "Menu.h"
#include "SubMenu.h"
#include "texture.h"

SubMenu::SubMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent) :
  Menu( parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth()*rel_w, parent->getHeight()*rel_h,
	parent->mRenderer, parent->mWindow, parent->mTextMaker )
{
  setRelX(rel_x);
  setRelY(rel_y);
  setRelWidth(rel_w);
  setRelHeight(rel_h);
  
  setParent(parent);

  setPositions();
}

SubMenu::~SubMenu()
{}

void SubMenu::render()
{
  if ( isActive() )
    {
      //render self relative to the parent and update self to actual coords
      setPositions();
      renderTexture(mTexture, mRenderer, getPosX(), getPosY(), getWidth(), getHeight() );
      //then render buttons and submenu
      renderSubItems();
    }
}

void SubMenu::setPositions()
{
  setPosX( mParent->getPosX() + mRel_x );
  setPosY( mParent->getPosY() + mRel_y ); 
  setWidth( mParent->getWidth() * mRelWidth );
  setHeight( mParent->getHeight() * mRelHeight );
}
