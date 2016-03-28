//Base class for TextBoxs
//
//Kevin Maguire
//13/09/2015
//

//-------------------------------------------------------------------------------------

#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <string>
#include <iostream>

#include "TextBox.h"
#include "TextLine.h"
#include "TextMaker.h"
#include "Button.h"

//-------------------------------------------------------------------------------------

class TextBox
{
 public:
 
  //TextBox(float x, float y, float width, float height, std::vector<std::string> words, TextMaker * maker);
  TextBox(float x, float y, float width, float height, std::string splitline, TextMaker * maker);
  virtual ~TextBox();
  bool collide(float x, float y);
  void makeLines();
  void outcome();
  void render();

  void setActive(bool b);
    
  float getHeight()
  {
    return mHeight;
  }
  TextLine* getLine(int e)
  {
    return mLines[e];
  }  
  float getPosX()
  {
    return mPosX;
  }
  float getPosY()
  {
    return mPosY;
  }
  int getScroll()
  {
    return mScroll;
  }
  TextMaker * getTextMaker()
  {
    return mTextMaker;
  }
  float getWidth()
  {
    return mWidth;
  }
  std::string getWord(int e)
  {
    return mWords[e];
  }  
  bool isActive()
  {
    return mActive;
  }
  void setHeight(float h)
  {
    mHeight = h;
  }
  void setPosX(float x)
  {
    mPosX = x;
  }
  void setPosY(float y)
  {
    mPosY = y;
  }
  void setScroll(int s)
  {
    mScroll = s;
  }
  void setTextMaker(TextMaker * maker)
  {
    mTextMaker = maker;
  }
  void setWords(std::vector<std::string> words)
  {
    mWords = words;
  }
  void setWidth(float w)
  {
    mWidth = w;
  }

 protected:
  std::vector<std::string> mWords;
  std::vector<TextLine*> mLines;
  
 private:
  
  float mPosX;
  float mPosY;
  float mWidth;
  float mHeight;
  
  bool mActive;

  TextMaker * mTextMaker;

  //for scrolling
  Button* mScrollButtonUp = nullptr;
  Button* mScrollButtonDown = nullptr;
  int mMaxLines;
  int mScroll = 0;

};

std::vector<std::string> makeVectorString(std::string ts, char splitchar);
ReturnContainer ScrollTextBoxDown(ArgContainer args);
ReturnContainer ScrollTextBoxUp(ArgContainer args);

#endif
