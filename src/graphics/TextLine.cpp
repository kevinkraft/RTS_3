#include <sstream>

#include "texture.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "TextMaker.h"
#include "logging.h"
#include "TextLine.h"
#include "Map.h"

//Note:
// * coordinates are screen coords

TextLine::TextLine(float x, float y, float w, float h, std::string message, TextMaker * maker)
{
  mTexture = nullptr;

  setPosX(x);
  setPosY(y);
  setWidth(w);
  setHeight(h);
  setTextMaker(maker);

  //loadText(message);
  setText(message);

  setActive(false);
}

TextLine::TextLine(std::string message, TextMaker * maker) 
  : TextLine(0., 0., 0., 0., message, maker)
{}

TextLine::~TextLine()
{
  std::cout << "Deleting TextLine" << std::endl;
}

int TextLine::getLineHeight()
{
  //get the height in pixels of the line
  return getTextureHeight( mTexture );
}

void TextLine::loadText(std::string message)
{
  //We need to first render to a surface as that's what TTF_RenderText
  //returns, then load that surface into a texture
  TTF_Font * font = mTextMaker->getFont(); 
  SDL_Renderer * renderer = mTextMaker->mRenderer; 
  SDL_Surface * surf = TTF_RenderText_Blended(font, mText.c_str(), mColour);
  if (surf == nullptr){
    logSDLError(std::cout, "TTF_LoadTextLine");
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

void TextLine::loadText(std::string message, SDL_Color colour)
{
  setColour(colour);
  loadText(message);
}

void TextLine::render()
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
