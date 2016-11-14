//Base class for TextLines
//
//Kevin Maguire
//13/09/2015
//

//-------------------------------------------------------------------------------------

#ifndef TEXTLINE_H_
#define TEXTLINE_H_

#include <string>
#include <iostream>

#include "TextLine.h"
#include "TextMaker.h"

//-------------------------------------------------------------------------------------

class TextLine
{
 public:
 
  TextLine(float x, float y, float width, float height, std::string message, TextMaker * maker);
  TextLine(std::string message, TextMaker * maker);
  virtual ~TextLine();
  
  int getLineHeight();
  void loadText(std::string);
  void loadText(std::string, SDL_Color colour);
  void render();

  SDL_Color getColour()
  {
    return mColour;
  }
  float getHeight()
  {
    return mHeight;
  }
  std::string getText()
  {
    return mText;
  }
  float getPosX()
  {
    return mPosX;
  }
  float getPosY()
  {
    return mPosY;
  }
  TextMaker * getTextMaker()
  {
    return mTextMaker;
  }
  float getWidth()
  {
    return mWidth;
  }
  bool isActive()
  {
    return mActive;
  }
  void setActive(bool b)
  {
    mActive = b;
  }
  void setColour(SDL_Color colour)
  {
    mColour = colour;
  }
  void setHeight(float h)
  {

    mHeight = h;
  }
  void setText(std::string message)
  {
    mText = message;
    loadText(message);
  }
  void setPosX(float x)
  {
    mPosX = x;
  }
  void setPosY(float y)
  {
    mPosY = y;
  }
  void setTextMaker(TextMaker * maker)
  {
    mTextMaker = maker;
  }
  void setWidth(float w)
  {
    mWidth = w;
  }
  
  SDL_Texture *mTexture;

 private:

  float mPosX;
  float mPosY;
  float mWidth;
  float mHeight;
  
  std::string mText;
  SDL_Colour mColour = DEFAULT_TEXT_COLOUR;
  bool mActive;

  TextMaker * mTextMaker;


};

std::string makeString(float val);
//std::string makeString(int val);

namespace TerminalText
{
  void printTerminal(std::string message);
}

#endif
