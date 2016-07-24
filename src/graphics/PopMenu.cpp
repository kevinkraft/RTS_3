#include "PopMenu.h"
#include "Map.h"
#include "Button.h"
#include "TextMaker.h"

//Note:
// * This class is inherantly linked to Action classes and Entity classes
//   * if it is ever necessary to make over pop menus you can move some of the action/entity
//     stuff to those classes 
// * x and y are game coordinates
// * mRect is obsolete but may be needed for sub menus

PopMenu::PopMenu(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(x, y, w, h, renderer, window, textMaker), Menu(x, y, w, h, renderer, window, textMaker)
{
  setWidth(mItemWidth);
  setHeight(mItemHeight);
}

PopMenu::PopMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(0., 0., 0., 0., renderer, window, textMaker), Menu(0., 0., 0., 0., renderer, window, textMaker)
{
  std::cout << "PopMenu::PopMenu: INFO: In Second Constructor" << std::endl;
  //  setWidth(mItemWidth); //dont need to set these as they are done by default when the instance is created
  //setHeight(mItemHeight);
  //std::cout << getWidth() << std::endl;
  //std::cout << getHeight() << std::endl;
  setWidth(mItemWidth);
  setHeight(mItemHeight);
}

PopMenu::~PopMenu()
{}

bool PopMenu::outcome()
{
  if (mButtons.size() != 0)
    {
      ReturnContainer funcReturn;
      for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
	{
	  if ( (*it)->isPressed() )
	    {
	      funcReturn = (*it)->outcome();
	      break;
	    }
	}
      if (funcReturn.mAction != nullptr)
	{
	  if (mSelectedEntity == nullptr)
	    {
	      std::cout << "PopMenu::outcome: INFO: mSelectedEntity is a nullptr" << std::endl;
	      return true;
	    }
	  std::cout << "PopMenu::outcome: INFO: After checking for null pointer" << std::endl;
	  mSelectedEntity->clearAddAction(funcReturn.mAction);
	  return true;
	}
      else if ( funcReturn.mOutcome != 0) //this could be done better
	{
	  std::cout << "PopMenu::outcome: WARN: Integer outcome is not the correct return type." << std::endl;
	  return true;
	}
    }
  else
    {
      std::cout << "Menu::outcome: WARN: This Menu has no outcomes." << std::endl;
      return true;
    }
  return true;
}

void PopMenu::scaleHeight()
{
  
  setHeight(mItemHeight * getSizeButtons());
}

void PopMenu::setXYPositions(float x, float y, float cameraoffset_x, float cameraoffset_y, float zoom)
{
  setPosX(x);
  setPosY(y);
  setGamePosX( getIsoX(x, y, cameraoffset_x, cameraoffset_y, zoom) );
  setGamePosY( getIsoY(x, y, cameraoffset_x, cameraoffset_y, zoom) );
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {

    }
}

void PopMenu::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if ( isActive() )
    {
      float rectposx = getPixelX(mGamePosX, mGamePosY, cameraoffset_x, cameraoffset_y, zoom);
      float rectposy = getPixelY(mGamePosX, mGamePosY, cameraoffset_x, cameraoffset_y, zoom);
      //update the screen pos coords to match the game coords
      setPosX( rectposx );
      setPosY( rectposy );
      renderTexture( mTexture, mRenderer, rectposx, rectposy, getWidth(), getHeight() );
      //render buttons
      float rel_h = 1./(mButtons.size() + 0.0);
      float rel_y = 0.;
      for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
	{
	  //need to reset the button coords to game coords so it doesnt move with the screen
	  (*it)->setRelX( 0 );
	  (*it)->setRelY( rel_y );
	  (*it)->setRelWidth( 1 );
	  (*it)->setRelHeight( rel_h );
	  (*it)->setWidth( this->getWidth() * 1 );
	  (*it)->setHeight( this->getHeight() * rel_h );
	  (*it)->setPosX( this->getPosX() );
	  (*it)->setPosY( this->getPosY() + rel_y );
	  (*it)->render(false);
	  rel_y += this->mItemHeight;
	}
    }
}

