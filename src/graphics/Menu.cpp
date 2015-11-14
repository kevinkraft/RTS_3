#include "Menu.h"
#include "texture.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Map.h"
#include "Button.h"

//Note:
// * x and y are game coordinates
// * mRect is obsolete but may be needed for sub menus

//Add:
// * When you add submenusand tabs lots of things will need to be added here

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

  setActive(false);
}

Menu::~Menu()
{
  std::cout << "Deleting Menu" << std::endl;
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
}

void Menu::addButton(Button * button)
{
  mButtons.push_back(button);
}

void Menu::clear()
{
  setActive(false);
  for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
    {
      delete (*it);
    }
  mButtons.clear();
}

void Menu::loadImage(std::string filename)
{
  mTexture = loadTexture(filename, mRenderer, true);
}

void Menu::outcome()
{
  std::cout << "Menu::outcome: ERROR: This Menu has no outcomes." << std::endl;
}

void Menu::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if (mActive)
    {
      float rectposx = getPixelX(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom);
      float rectposy = getPixelY(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom);
      std::cout << rectposx << " map " << rectposy << std::endl; 
      renderTexture(mTexture, mRenderer, rectposx, rectposy, mWidth, mHeight);
      //render buttons
      for(std::vector<Button*>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
	{
	  (*it)->render(cameraoffset_x, cameraoffset_y, zoom, this);
	}
    }
}

void Menu::setPositions(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  //x and y are screen pixel positions so they need to be converted
  setPosX(getIsoX(x, y, cameraoffset_x, cameraoffset_y, zoom));
  setPosY(getIsoY(x, y, cameraoffset_x, cameraoffset_y, zoom));
}
