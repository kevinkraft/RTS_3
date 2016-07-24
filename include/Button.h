#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "TextLine.h"
#include "DisplayPiece.h"

#include "FunctionCaller.h"

class Menu;

//Note:
// * members are relative to the menu in which the button is contained
// * the DisplayPiece of the parent menu becomes the Button DisplayPiece parent

class Button : public DisplayPiece
{
 public:
  
  //Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, int outcome,
  //	 SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler);
  Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, int outcome, DisplayPiece * parent);
  Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, int outcome, Menu * menu);
  Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	 DisplayPiece * parent);
  Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	 Menu * menu);
  //Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
  //SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler);
			
  virtual ~Button();

  bool collide(float pos_x, float pos_y, DisplayPiece * parent);
  bool collide(float pos_x, float pos_y);
  void makeTitleTextLine();
  ReturnContainer outcome();
  //void render(float posx, float posy, float width, float height);
  //void render(Menu * menu);
  void render(bool resetPos = true);
  //void render(TextBox * tb);

  ArgContainer getArgContainer()
  {
    return mArgContainer;
  }
  FunctionCaller getFunctionCaller()
  {
    return mFunctionCaller;
  }
  int getOutcome()
  {
    return mOutcome;
  }
  //  float getRelHeight()
  //{
  //  return mRelHeight;
  //}  
  /*float getRelPosX()
  {
    return mRel_x;
  }
  float getRelPosY()
  {
    return mRel_y;
  }
  float getRelWidth()
  {
    return mRelWidth;
    }*/
  TextLine * getTitle()
  {
    return mTitle;
  }
  std::string getTitleString()
  {
    return mTitleString;
  }
  bool isHighlighted()
  {
    return mHighlight;
  }
  bool isPressed()
  {
    return mPressed;
  }
  void setArgContainer(ArgContainer args)
  {
    mArgContainer = args;
  }
  void setFunctionCaller(FunctionCaller caller)
  {
    mFunctionCaller = caller;
  }
  void setHighlight(bool b)
  {
    mHighlight = b;
  }
  void setOutcome(int outcome)
  {
    mOutcome = outcome;
  }
  void setPressed(bool p)
  {
    mPressed = p;
  }
  /*void setRelHeight(float h)
  {
    mRelHeight = h;
  }
  void setRelPosX(float posx)
  {
    mRel_x = posx;
  }
  void setRelPosY(float posy)
  {
    mRel_y = posy;
  }
  void setRelWidth(float w)
  {
    mRelWidth = w;
    }*/
  void setTitleString(std::string t)
  {
    mTitleString = t;
  }
  
  /*  SDL_Texture *mTexture;
  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;*/
  //TextMaker * mTextMaker;

 private:
  /*  float mRel_x;
  float mRel_y;
  float mRelWidth;
  float mRelHeight;*/

  std::string mTitleString;
  bool mPressed;

  int mOutcome;
  FunctionCaller mFunctionCaller;
  ArgContainer mArgContainer;

  TextLine * mTitle;

  bool mHighlight;
};

#endif
