//Base class for Messages
//
//Kevin Maguire
//13/09/2015
//

//-------------------------------------------------------------------------------------

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"

#include "Message.h"
#include "TextMaker.h"

//-------------------------------------------------------------------------------------

class Message
{
 public:
 
  Message(float x, float y, float width, float height, std::string message, TextMaker * maker);
  Message(std::string message, TextMaker * maker);
  virtual ~Message();
  
  void loadMessage(std::string);
  void loadMessage(std::string, SDL_Color colour);
  void render(int cameraoffset_x, int cameraoffset_y, float zoom);

  SDL_Color getColour()
  {
    return mColour;
  }
  float getHeight()
  {
    return mHeight;
  }
  std::string getMessage()
  {
    return mMessage;
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
  void setMessage(std::string message)
  {
    mMessage = message;
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
  
  std::string mMessage;
  SDL_Colour mColour = DEFAULT_TEXT_COLOUR;
  bool mActive;

  TextMaker * mTextMaker;

};

#endif
