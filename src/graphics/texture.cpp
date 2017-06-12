#include "texture.h"
#include "logging.h"
#include "SDL.h"
#include "SDL_image.h"

//Add:
// * another function which accepts a rectangle rather than making one

int getTextureHeight(SDL_Texture* texture)
{
  //seems to give a value which is too large so I divided by 2
  int w(0);
  int h(0);
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  return h/2.;
}

int getTextureWidth(SDL_Texture* texture)
{
  //seems to give a value which is too large so I divided by 2
  int w(0);
  int h(0);
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  return w/2.;
}


SDL_Texture *loadTexture(std::string file, SDL_Renderer *renderer, bool colorkey)
{
  SDL_Texture *texture = nullptr;
  SDL_Surface *loadedImage = IMG_Load(file.c_str());

  if (loadedImage != nullptr)
    {
      if (colorkey)
	{
	  SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0xFF));	//Cyan.
	}
      //std::cout << "INFO: texture:loadTexture: In This Function Before making texture" << std::endl;
      if ( renderer == nullptr )
	{
	  std::cout << "INFO: texture:loadTexture: renderer is NULL" << std::endl;
	}
      texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
      //std::cout << "INFO: texture:loadTexture: In This Function After making texture" << std::endl;
      SDL_FreeSurface(loadedImage);
      if (texture == nullptr)
	logSDLError(std::cout, "CreateTextureFromSurface");
    }
  else
    logSDLError(std::cout, "LoadBMP");

  return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst)
{
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  renderTexture(texture, renderer, x, y, w, h);
}

/*void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y)
{
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  renderTexture(texture, renderer, x, y, w, h);
}*/
