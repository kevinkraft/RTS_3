#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextMaker.h"
#include "logging.h"

TextMaker::TextMaker(std::string fontFile, SDL_Renderer *renderer, SDL_Window *window)
{
  mRenderer = nullptr;
  mWindow = nullptr;

  mRenderer = renderer;
  mWindow = window;

  setFontFile(fontFile);

  openFont();

  //setActive(false);
}

TextMaker::~TextMaker()
{
  std::cout << "TextMaker::~TexMaker: INFO: Closing Font " << std::endl;
  TTF_CloseFont(mFont);
  std::cout << "Deleting TextMaker" << std::endl;
}

void TextMaker::openFont()
{
  //Open the font
  std::cout << "TextMaker::openFont: INFO: Before Opening the font" << std::endl;
  TTF_Font *font = TTF_OpenFont(mFontFile.c_str(), mFontSize);
  if (font == nullptr){
    logSDLError(std::cout, "TTF_OpenFont");
  }
  std::cout << "TextMaker::openFont: INFO: After Opening the font" << std::endl;
  mFont = font;
}

