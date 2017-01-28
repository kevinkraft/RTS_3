#include "Sprite.h"
#include "texture.h"
#include "Map.h"
#include "SDL.h"
#include "SDL_image.h"

Sprite::Sprite(std::string filename, float x, float y, SDL_Renderer *renderer, SDL_Window *window, float scale)
{
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;

  mTexture = loadTexture(filename, renderer, true);

  mRenderer = renderer;
  mWindow = window;

  setPosX(x);
  setPosY(y);

  setScale(scale);
  //SDL_Rect * mRect = new SDL_Rect()

}

Sprite::Sprite(float x, float y, float click_w, float click_h, float click_offset_x, float click_offset_y, float scale)
{
  //click w and h define the width and height of click collide rect, offset are pos corrections
  mFilename = "res/images/iso/map/0.png";
  setPosX(x);
  setPosY(y);
  mRenderer = nullptr;
  mWindow = nullptr;
  setClickHeight(click_h);
  setClickWidth(click_w);
  setClickOffsetX(click_offset_x);
  setClickOffsetY(click_offset_y);
  setScale(scale);
}

Sprite::~Sprite()
{
  std::cout << "Deleting sprite" << std::endl;
}

bool Sprite::collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  //check collision where xtol/ytol is the up/left tolerance
  //all coords in game coords
  std::cout << "Sprite::collide: INFO: Checking collison" << std::endl;
  float sposx = getPixelX(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom, mScale);
  float sposy = getPixelY(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom, mScale);
  sposx += mClickOffset_x * zoom;
  sposy += mClickOffset_y * zoom;
  float xtol = mClickWidth * zoom;
  float ytol = mClickHeight * zoom;
  if (
      (x - sposx < xtol) && (y - sposy < ytol) &&
      (x - sposx > 0) && (y - sposy > 0)
       )
    {
      return true;
    }
  return false;
}

void Sprite::loadImage()
{
  std::cout << "Loading unit texture" << std::endl;
  //mTexture = loadTexture(mFilename, mRenderer, mWindow);
  mTexture = loadTexture(mFilename, mRenderer, true);
  if (mTexture == nullptr)
    {
      std::cout << "Sprite::loadImage: ERROR: Image file not found" << std::endl;
    }
  std::cout << "INFO: Leaving Sprite::loadImage" << std::endl;
}

void Sprite::render(int cameraoffset_x, int cameraoffset_y, float zoom, int height)
{
  float pixel_x = 0;
  float pixel_y = 0;
  pixel_y = getPixelY(getPosX(), getPosY(), cameraoffset_x, cameraoffset_y, zoom, mScale) - height;
  pixel_x = getPixelX(getPosX(), getPosY(), cameraoffset_x, cameraoffset_y, zoom, mScale);

  //Render only whats visible:
  const int offscreen_tolerance = 3*TILE_SIZE*zoom;
  int screen_width;
  int screen_height;
  SDL_GetWindowSize(mWindow, &screen_width, &screen_height);

  if ((pixel_x >= 0-offscreen_tolerance) or
      (pixel_x+TILE_SIZE*zoom <= screen_width+offscreen_tolerance) or
      (pixel_y >= 0-offscreen_tolerance) or
      (pixel_y+TILE_SIZE*zoom <= screen_height+offscreen_tolerance))
    {
      renderTexture(mTexture, mRenderer, pixel_x, pixel_y, mScale*zoom, mScale*zoom);
    }
}

/*float Sprite::getPixelX(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  float pixel_x = 0;
  pixel_x = (TILE_SIZE*zoom * getPosX() * 0.5) + (TILE_SIZE*zoom * getPosY() * 0.5) - cameraoffset_x;

  return pixel_x;
}

float Sprite::getPixelY(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  float pixel_y = 0;
  pixel_y = ((TILE_SIZE*zoom * getPosX() * 0.25) - (TILE_SIZE*zoom * getPosY() * 0.25)) - cameraoffset_y;

  return pixel_y;
  }*/

float Sprite::getZOrder()
{
  return getPixelY(0,0);
}
