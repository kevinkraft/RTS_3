#include "texture.h"
#include "SDL.h"
#include "SDL_image.h"
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
// * Move everything to do with a relative display piece into this class

DisplayPiece::DisplayPiece(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler)
{
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTextMaker = nullptr;

  mRenderer = renderer;
  mWindow = window;
  mTextMaker = TextHandler;

  mRect = new SDL_Rect();

  setPosX(x);
  setPosY(y);
  setWidth(w);
  setHeight(h);

  this->loadImage("res/images/menu/menu.png");

  setActive(false);
}

DisplayPiece::DisplayPiece(float rel_x, float rel_y, float rel_w, float rel_h, DisplayPiece * parent)
  : DisplayPiece( parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent->mRenderer,
		  parent->mWindow, parent->mTextMaker )
{
  std::cout << "INFO: DisplayPiece::DisplayPiece:2 In the 2nd constructor" << std::endl;
  setRelX(rel_x);
  setRelY(rel_y);
  setRelWidth(rel_w);
  setRelHeight(rel_h);
  std::cout << "INFO: DisplayPiece::DisplayPiece:2 Loading the image" << std::endl;
  setPositions();
}

/*DisplayPiece::DisplayPiece()
{
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTextMaker = nullptr;

  mRect = new SDL_Rect();

  setPosX(0.);
  setPosY(0.);
  setWidth(0.);
  setHeight(0.);

  this->loadImage("res/images/menu/menu.png");

  setActive(false);
  }*/

DisplayPiece::~DisplayPiece()
{}

void DisplayPiece::loadImage(std::string filename)
{
  mTexture = loadTexture(filename, mRenderer, true);
}

void DisplayPiece::setActive(bool b)
{
  mActive = b;
}

void DisplayPiece::setPositions()
//I'm not conviced that this actually works
{
  DisplayPiece * parent = getParent();
  if ( parent )
    {
      //set up the relative display piece so that it is ready to be printed to the screen
      float posx = parent->getPosX();
      float posy = parent->getPosY();
      float width = parent->getWidth();
      float height = parent->getHeight();
      this->setPosX(  posx + mRel_x );
      this->setPosY( posy + mRel_y );
      this->setWidth( width * mRelWidth );
      this->setHeight( height * mRelHeight );
    }
}


