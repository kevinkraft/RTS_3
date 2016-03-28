#include <string>
#include <sstream>
#include <vector>

#include "TextBox.h"
#include "texture.h"
#include "global.h"

//Note:
// * This class is always contained within something else.
//   a menu for example
// * The idea is to put this onto a menu
// * coordinates are screen coords

//Add:
// * Change the message font size if the text box is not big enough, not long enough
//   * no, a better idea is to add a scroll function

TextBox::TextBox(float x, float y, float w, float h, std::string splitline, TextMaker* maker)
{
  setPosX(x);
  setPosY(y);
  setWidth(w);
  setHeight(h);
  std::vector<std::string> words = makeVectorString(splitline, ' ');
  setWords(words);
  setTextMaker(maker);
  makeLines();  
  setActive(false);
}

TextBox::~TextBox()
{
  std::cout << "Deleting TextBox" << std::endl;
  for(std::vector<TextLine*>::iterator it = mLines.begin(); it != mLines.end(); ++it)
    {
      delete (*it);
    }
}

bool TextBox::collide(float x, float y)
{
  //check if the text box scroll buttons were clicked
  if ( mScrollButtonUp != nullptr)
    {
      if ( mScrollButtonUp->collide(x, y) == true || mScrollButtonDown->collide(x, y) == true )
	{
	  return true;
	}
    }
  return false;
}

void TextBox::makeLines()
{
  //ADD:
  // * Add to this function so that the height of the text box is not exceeded, it currently can be.
  //make an offset to give some tolerance to the menu edge
  float xoff = mWidth/17.; 
  float yoff = mHeight/20.; 
  //split the words into a vector of TextLines based on the width of the text box
  std::vector<TextLine*> lines;
  int step = 0;
  std::string lstring = "";
  std::string lstring_prev = "";
  TextLine * oline;
  double text_height = 50.; //this doesn't define the text height to be 50 pixels, unclear 
  for(std::vector<std::string>::iterator it = mWords.begin(); it != mWords.end(); ++it)
    {
      TextLine * line;
      lstring = lstring + (*it) + " ";
      line = new TextLine( xoff + mPosX, yoff + mPosY + step*30., lstring.size()*10., text_height, lstring, mTextMaker);
      if ( getTextureWidth(line->mTexture) >= mWidth )
	{
	  line = new TextLine( xoff + mPosX, yoff + mPosY + step*30., lstring_prev.size()*10., text_height, lstring_prev, mTextMaker);
	  lines.push_back(line);
	  step++;
	  lstring = (*it)+ " ";
	}
      lstring_prev = lstring;
    }
  //last line
  oline = new TextLine( xoff + mPosX, yoff + mPosY + step*30., lstring.size()*10., text_height, lstring, mTextMaker);
  lines.push_back(oline);
  mLines = lines;

  //check if the text length is greater than the text box length and make scroll
  if ( mHeight < ACTUAL_TEXT_HEIGHT * mLines.size() ) //tuned actual text height
    {
      //make the scroll buttons
      ArgContainer args = ArgContainer();
      args.mTextBox = this;
      float bscale = 13./14.;
      mScrollButtonUp = new Button( bscale * mWidth, 0., 1-bscale, 1-bscale, "<", &ScrollTextBoxUp, args,
				   mTextMaker->mRenderer, mTextMaker->mWindow, mTextMaker);
      mScrollButtonDown = new Button(bscale * mWidth, 0., 1-bscale, 1-bscale, ">", &ScrollTextBoxDown, args,
				     mTextMaker->mRenderer, mTextMaker->mWindow, mTextMaker);
      mMaxLines = floor( mHeight / text_height );
    }
}


void TextBox::outcome()
{
  if ( mScrollButtonUp )
    {
      //these default functions dont need anything done on the returns
      ReturnContainer funcReturn;
      funcReturn = mScrollButtonUp->outcome();
      funcReturn = mScrollButtonDown->outcome();
    }
}

void TextBox::render()
{
  //if scroll buttons are defined only render the correct lines
  std::vector<TextLine*> rlines(0);
  if ( mScrollButtonUp )
    {
      //std::cout << "TextBox:render INFO: The Text is Too Long and a Scroll Function Will Be Implemented" << std::endl;
      std::vector<TextLine*> stub( &mLines[ mScroll * mMaxLines ], &mLines[ mMaxLines + mMaxLines * mScroll + 1 ] );
      rlines = stub;
      mScrollButtonUp->render(this);
      mScrollButtonDown->render(this);
    }
  else
    {
      rlines = mLines;
    }
  for(std::vector<TextLine*>::iterator it = rlines.begin(); it != rlines.end(); ++it)
    {
      (*it)->render();
    }
  
}

void TextBox::setActive(bool b)
{
  mActive = b;
  for(std::vector<TextLine*>::iterator it = mLines.begin(); it != mLines.end(); ++it)
    {
      (*it)->setActive(b);
    }
}

//-------------------------------------------------------------------------------------
// Non-Member Functions
//-------------------------------------------------------------------------------------

std::vector<std::string> makeVectorString(std::string ts, char splitchar)
{
  //takes the string ts and splits it into a vector of strings when it finds a splitchar character
  //i.e. it splits the string by spaces if splitchar is a space
  std::vector<std::string> rvec;
  std::stringstream ss(ts);
  std::string item;
  while ( std::getline( ss, item, splitchar ) ) 
    {
      rvec.push_back(item);
    }
  /*  for(std::vector<std::string>::iterator it = rvec.begin(); it != rvec.end(); ++it)
    {
      std::cout << (*it) << std::endl;
      }*/
  return rvec;
}

ReturnContainer ScrollTextBoxDown(ArgContainer args)
{
  //add 1 to mScroll
  args.mTextBox->setScroll( args.mTextBox->getScroll() + 1 );
  return ReturnContainer();
}

ReturnContainer ScrollTextBoxUp(ArgContainer args)
{
  //subtract 1 from mScroll
  args.mTextBox->setScroll( args.mTextBox->getScroll() - 1 );
  return ReturnContainer();
}

