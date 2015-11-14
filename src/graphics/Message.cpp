#include "texture.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "TextMaker.h"
#include "logging.h"
#include "Message.h"
#include "Map.h"

//Note:
// * This class is always contained within something else. A button
//   or a menu for example
// * coordinates are game coordinates

Message::Message(float x, float y, float w, float h, std::string message, TextMaker * maker)
{
  mTexture = nullptr;

  setPosX(x);
  setPosY(x);
  setWidth(w);
  setHeight(h);
  setMessage(message);
  setTextMaker(maker);

  loadMessage(message);
  
  setActive(false);
}

Message::Message(std::string message, TextMaker * maker) 
  : Message(0., 0., 0., 0., message, maker)
{}

Message::~Message()
{
  std::cout << "Deleting Message" << std::endl;
}

void Message::loadMessage(std::string message)
{
  //We need to first render to a surface as that's what TTF_RenderText
  //returns, then load that surface into a texture
  TTF_Font * font = mTextMaker->getFont(); 
  SDL_Renderer * renderer = mTextMaker->mRenderer; 
  SDL_Surface * surf = TTF_RenderText_Blended(font, mMessage.c_str(), mColour);
  if (surf == nullptr){
    logSDLError(std::cout, "TTF_LoadMessage");
    mTexture = nullptr;
  }
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
  if (texture == nullptr){
    logSDLError(std::cout, "CreateTexture");
  }
  //Clean up the surface and font
  SDL_FreeSurface(surf);
  mTexture = texture;
}

void Message::loadMessage(std::string message, SDL_Color colour)
{
  setColour(colour);
  loadMessage(message);
}

void Message::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  if (mActive)
    {
      float rectposx = getPixelX(mPosX, mPosY, cameraoffset_x, cameraoffset_y, zoom);
      float rectposy = getPixelY(mPosX, mPosY, cameraoffset_x, cameraoffset_y, zoom);
      renderTexture(mTexture, mTextMaker->mRenderer, rectposx, rectposy, mWidth, mHeight);
    }
}

