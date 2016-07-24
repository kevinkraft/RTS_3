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

class TextBox: virtual public DisplayPiece
{
 public:
 
  //TextBox(float x, float y, float width, float height, std::vector<std::string> words, TextMaker * maker);
  TextBox(float rel_x, float rel_y, float rel_w, float rel_h, std::string splitline, TextMaker * maker, DisplayPiece * parent);
  TextBox(float rel_x, float rel_y, float rel_w, float rel_h, std::string splitline, TextMaker * maker, Menu * menu);
  virtual ~TextBox();
  bool collide(float x, float y);
  void makeLines();
  void outcome();
  void render();

  using DisplayPiece::setActive;
  void setActive(bool b);

  TextLine* getLine(int e)
  {
    return mLines[e];
  }  
  std::vector<TextLine*> getLines()
  {
    return mLines;
  }  
  int getMaxLines()
  {
    return mMaxLines;
  }  
  int getScroll()
  {
    return mScroll;
  }
  Button * getScrollButtonDown()
  {
    return mScrollButtonDown;
  }
  Button * getScrollButtonUp()
  {
    return mScrollButtonUp;
  }
  TextMaker * getTextMaker()
  {
    return mTextMaker;
  }
  std::string getWord(int e)
  {
    return mWords[e];
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

 protected:
  std::vector<std::string> mWords;
  std::vector<TextLine*> mLines;
  
 private:
  
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
