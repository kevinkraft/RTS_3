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
  : Menu(x, y, w, h, renderer, window, textMaker)
{}

PopMenu::PopMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : Menu(0., 0., 0., 0., renderer, window, textMaker)
{
  std::cout << "CONSTRUCTING THE POP MENU" << std::endl;
  setWidth(mItemWidth);
  setHeight(mItemHeight);
  //std::cout << getWidth() << std::endl;
  //std::cout << getHeight() << std::endl;
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

void PopMenu::setPositions(float x, float y, float cameraoffset_x, float cameraoffset_y, float zoom)
{
  setPosX(x);
  setPosY(y);
  setGamePosX( getIsoX(x, y, cameraoffset_x, cameraoffset_y, zoom) );
  setGamePosY( getIsoY(x, y, cameraoffset_x, cameraoffset_y, zoom) );
}

void PopMenu::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if ( isActive() )
    {
      float rectposx = getPixelX(mGamePosX, mGamePosY, cameraoffset_x, cameraoffset_y, zoom);
      float rectposy = getPixelY(mGamePosX, mGamePosY, cameraoffset_x, cameraoffset_y, zoom);
      renderTexture( mTexture, mRenderer, rectposx, rectposy, getWidth(), getHeight() );
      //update the screen pos coords to match the game coords
      setPosX( rectposx );
      setPosY( rectposy );
      //render buttons
      for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
	{
	  (*it)->render(this);
	}
    }
}

