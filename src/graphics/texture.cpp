#include "texture.h"
#include "logging.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


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
      texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
      SDL_FreeSurface(loadedImage);
      if (texture == nullptr)
	logSDLError(std::cout, "CreateTextureFromSurface");
    }
  else
    logSDLError(std::cout, "LoadBMP");
  
  return texture;
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
