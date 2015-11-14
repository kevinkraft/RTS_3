#include "Sprite.h"
#include "texture.h"
#include "Map.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

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
}

Sprite::Sprite(float x, float y, float scale)
{
  mFilename = "res/images/iso/map/0.png";
  setPosX(x);
  setPosY(y);
  mRenderer = nullptr;
  mWindow = nullptr;  
  setScale(scale);
}

Sprite::~Sprite()
{
  std::cout << "Deleting sprite" << std::endl;
}

bool Sprite::collide(float x, float y, float xtol, float ytol, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  //check collision where xtol/ytol is the up/left tolerance
  //all coords in game coords
  std::cout << "Sprite::collide: INFO: Checking collison" << std::endl;
  float sposx = getPixelX(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom, mScale);
  float sposy = getPixelY(mPos_x, mPos_y, cameraoffset_x, cameraoffset_y, zoom, mScale); 
  sposx += UNIT_CLICK_COLLIDE_OFFSET_X;
  sposy += UNIT_CLICK_COLLIDE_OFFSET_Y;
  //float sposx = mPos_x;
  //float sposy = mPos_y;
  //float stolx = getPixelX(xtol, ytol, cameraoffset_x, cameraoffset_y, zoom);
  //float stoly = getPixelY(xtol, ytol, cameraoffset_x, cameraoffset_y, zoom); 
  std::cout << "sposx: " << sposx << std::endl;
  std::cout << "sposy: " << sposy << std::endl;
  std::cout << "xtol: " << xtol << std::endl;
  std::cout << "ytol: " << ytol << std::endl;
  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
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
