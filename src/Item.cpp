#include "Item.h"

Item::Item(float pos_x, float pos_y, int type, int amount)
{  
  setPosX(pos_x);
  setPosY(pos_y);

  mSprite = new Sprite(pos_x, pos_y);

  setType(type);
  setAmount(amount);

}

Item::~Item()
{
  //std::cout << "Deleting Item" << std::endl;
}

/*void Item::render(int cameraoffset_x, int cameraoffset_y, float zoom, int height)
{
  float pixel_x = 0;
  float pixel_y = 0;
  
  pixel_y = getPixelY(cameraoffset_x, cameraoffset_y, zoom) - height;
  pixel_x = getPixelX(cameraoffset_x, cameraoffset_y, zoom);
  
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
      renderTexture(mTexture, mRenderer, pixel_x, pixel_y, TILE_SIZE*zoom, TILE_SIZE*zoom);
    }
    }*/

