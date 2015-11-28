//#include "Menu.h"
#include "SubMenu.h"
#include "texture.h"

SubMenu::SubMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent) :
  Menu( parent->getPosX(), parent->getPosY(), parent->getWidth(), parent->getHeight(),
	parent->mRenderer, parent->mWindow, parent->mTextMaker )
{
  setRelX(rel_x);
  setRelY(rel_y);
  setRelWidth(rel_w);
  setRelHeight(rel_h);
  
  setParent(parent);
  
}

SubMenu::~SubMenu()
{}

void SubMenu::render()
{
  if ( isActive() )
    {
      //render self relative to the parent and update self to actual coords
      setPosX( mParent->getPosX() + mRel_x );
      setPosY( mParent->getPosY() + mRel_y ); 
      setWidth( mParent->getWidth() * mRelWidth );
      setHeight( mParent->getHeight() * mRelHeight );
      renderTexture(mTexture, mRenderer, getPosX(), getPosY(), getWidth(), getHeight() );
      //then render buttons and submenu
      //renderSubItems();
    }
}

