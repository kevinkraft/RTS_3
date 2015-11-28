#include <sstream>

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
// * coordinates are screen coords

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

void Message::render()
{
  if (mActive)
    {
      renderTexture(mTexture, mTextMaker->mRenderer, mPosX, mPosY, mWidth, mHeight);
    }
}


//-------------------------------------------------------------------------------------
// Other Functions
//-------------------------------------------------------------------------------------

std::string makeString(float val)
{
  std::stringstream sstrval;
  sstrval << val;
  std::string strval = sstrval.str();
  return strval;
}

std::string makeString(int val)
{
  std::stringstream sstrval;
  sstrval << val;
  std::string strval = sstrval.str();
  return strval;
}


void printTerminal(std::string message)
{
  std::cout << message << std::endl;
}
