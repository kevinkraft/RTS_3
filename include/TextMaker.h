//Base class for text
//
//Kevin Maguire
//13/09/2015
//

//-------------------------------------------------------------------------------------

#ifndef TEXTMAKER_H_
#define TEXTMAKER_H_

#include <string>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"

#include "global.h"


//-------------------------------------------------------------------------------------

class TextMaker
{
 public:
  
  TextMaker(std::string fontFile, SDL_Renderer *renderer, SDL_Window *window);
  virtual ~TextMaker();

  void openFont();
    
  TTF_Font * getFont()
  {
    return mFont;
  }
  std::string getFontFile()
  {
    return mFontFile;
  }
  int getFontSize()
  {
    return mFontSize;
  }
  void setFont(TTF_Font * font)
  {
    mFont = font;
  }
  void setFontFile(std::string fontpath)
  {
    mFontFile = fontpath;
  }
  void setFontSize(int size)
  {
    mFontSize = size;
  }

  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;
 
 private:

  std::string mFontFile;
  TTF_Font * mFont;
  int mFontSize = DEFAULT_FONT_SIZE;

};

#endif
