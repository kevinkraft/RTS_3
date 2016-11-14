#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "TextBox.h"
#include "Menu.h"
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

TextBox::TextBox(float rel_x, float rel_y, float rel_w, float rel_h, std::string splitline, TextMaker* maker, DisplayPiece * parent)
  : DisplayPiece(rel_x, rel_y, rel_w, rel_h, parent)
{
  std::cout << "INFO: TextBox::TextBox:1 In First Constructor " << std::endl;
  std::vector<std::string> words = makeVectorString(splitline, ' ');
  setParent(parent);
  setTextMaker(maker);
  setWords(words);
  //makeLines();  
  std::cout << "INFO: TextBox::TextBox:1 Leaving Constructor " << std::endl;
}

TextBox::TextBox(float rel_x, float rel_y, float rel_w, float rel_h, std::string splitline, TextMaker* maker, Menu * menu)
  : TextBox( rel_x, rel_y, rel_w, rel_h, splitline, maker, dynamic_cast<DisplayPiece*>(menu) )
{
  std::cout << "INFO: TextBox::TextBox:2 In Second Constructor " << std::endl;
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
  if ( mScrollButtonUp && mScrollButtonDown )
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
  std::cout << "INFO: TextBox::makeLines: In This Function " << std::endl;
  //make an offset to give some tolerance to the menu edge
  float xoff = this->getWidth()/17.; 
  float yoff = this->getHeight()/20.; 
  //split the words into a vector of TextLines based on the width of the text box
  std::vector<TextLine*> lines;
  int step = 0;
  std::string lstring = "";
  std::string lstring_prev = "";
  TextLine * oline;
  double text_height = 50.; //this doesn't define the text height to be 50 pixels, unclear 
  for(std::vector<std::string>::iterator it = mWords.begin(); it != mWords.end(); ++it)
    {
      std::string word = (*it);
      TextLine * line;
      std::regex vspace("#vspace\\d+");
      //std::cout << "INFO: TextBox:makeLines: The vspace regex is: " << "#vspace\\d+" << std::endl;
      //std::cout << "INFO: TextBox::makeLines: The Word is: " << word << std::endl;
      if ( regex_match(word, vspace) )
	{
	  std::cout << "INFO: TextBox::makeLines: Word Matches the vspace Regex. " << std::endl;
	  std::string spaces = std::string( std::stoi(word.substr(7)) , ' ');
	  word = spaces;
	}
      lstring = lstring + word + " ";
      line = new TextLine( xoff + this->getPosX(), yoff + this->getPosY() + step*30., lstring.size()*10., text_height, lstring, mTextMaker);
      //there are special words that add new lines and spaces
      if ( getTextureWidth(line->mTexture) >= this->getWidth() || word == "#newline" )
	{
	  if ( word == "#newline" ) word = "";
	  line = new TextLine( xoff + this->getPosX(), yoff + this->getPosY() + step*30., lstring_prev.size()*10., text_height, lstring_prev, mTextMaker);
	  lines.push_back(line);
	  step++;
	  lstring = word+ " ";
	}
      lstring_prev = lstring;
    }
  //last line
  oline = new TextLine( xoff + this->getPosX(), yoff + this->getPosY() + step*30., lstring.size()*10., text_height, lstring, mTextMaker);
  lines.push_back(oline);
  mLines = lines;

  //check if the text length is greater than the text box length and make scroll
  if ( this->getHeight() < ACTUAL_TEXT_HEIGHT * mLines.size() ) //tuned actual text height
    {
      //make the scroll buttons
      ArgContainer args = ArgContainer();
      args.mTextBox = this;
      float bscale = 13./14.;
      mScrollButtonUp = new Button( bscale * this->getWidth(), 0., 1-bscale, 1-bscale, "<", &ScrollTextBoxUp,
				    args, dynamic_cast<DisplayPiece*>(this) );
      mScrollButtonDown = new Button( bscale * this->getWidth(), bscale * this->getHeight(), 1-bscale, 1-bscale, ">", &ScrollTextBoxDown,
				      args, dynamic_cast<DisplayPiece*>(this) );
      mMaxLines = floor( this->getHeight() / ACTUAL_TEXT_HEIGHT );
    }
}


void TextBox::outcome()
{
  if ( mScrollButtonUp && mScrollButtonDown )
    {
      //these default functions dont need anything done on the returns
      ReturnContainer funcReturn;
      std::cout << "INFO: TextBox::outcome: Calling the Scroll Up button outcome " << std::endl;
      std::cout << "INFO: TextBox::outcome: mScrollButtonUp->isPressed() " << mScrollButtonUp->isPressed() << std::endl;
      funcReturn = mScrollButtonUp->outcome();
      funcReturn = mScrollButtonDown->outcome();
    }
}

void TextBox::render()
{
  //if scroll buttons are defined only render the correct lines
  std::vector<TextLine*> rlines(0);
  if ( mScrollButtonUp && mScrollButtonDown )
    {
      /*std::cout << "TextBox:render INFO: number of words: " <<  mWords.size() << std::endl;
      std::cout << "TextBox:render INFO: number of lines: " <<  mLines.size() << std::endl;
      std::cout << "TextBox:render INFO: max lines: " <<  mMaxLines << std::endl;
      std::cout << "TextBox:render INFO: scroll int: " <<  mScroll << std::endl;
      std::cout << "TextBox:render INFO: mScroll*mMaxLines: " <<  mScroll*mMaxLines << std::endl;
      std::cout << "TextBox:render INFO: mMaxLines + mScroll * mMaxLines: " <<  mMaxLines + mScroll * mMaxLines << std::endl;*/
      //std::vector<TextLine*> stub( &mLines[ mScroll * mMaxLines ], &mLines[ mMaxLines + mMaxLines * mScroll + 1 ] );
      int last_l = ( mMaxLines + mMaxLines * mScroll ) >= mLines.size() ? mLines.size() : mMaxLines + mMaxLines * mScroll ;
      std::vector<TextLine*> stub( &mLines[ mScroll * mMaxLines ], &mLines[ last_l] );
      rlines = stub;
      mScrollButtonUp->render();
      mScrollButtonDown->render();
    }
  else
    {
      rlines = mLines;
    }
  //for(std::vector<TextLine*>::iterator it = rlines.begin(); it != rlines.end(); ++it)
  for(int i = 0; i < rlines.size(); i++)
    {
      TextLine * rl = rlines[i];
      //add the y of the i-th line in the mLines list as the y pos of the i-th line in rlines
      rl->setPosY( mLines[i]->getPosY() );
      //render the lines
      rl->render();
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

void TextBox::setWords(std::vector<std::string> words)
{
  mWords = words;
  makeLines();
}

void TextBox::setWords( std::string splitline)
{
  std::vector<std::string> words = makeVectorString(splitline, ' ');
  mWords = words;
  makeLines();
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
  std::cout << "INFO: TextBox:ScrollTextBoxDown: mScroll is " << args.mTextBox->getScroll() << std::endl;
  TextBox * tb = args.mTextBox;
  if ( tb->getScroll() == floor(tb->getLines().size() / tb->getMaxLines()) )
    return ReturnContainer();
  args.mTextBox->setScroll( args.mTextBox->getScroll() + 1 );
  std::cout << "INFO: TextBox:ScrollTextBoxDown: mScroll is " << args.mTextBox->getScroll() << std::endl;
  return ReturnContainer();
}

ReturnContainer ScrollTextBoxUp(ArgContainer args)
{
  std::cout << "INFO: TextBox:ScrollTextBoxUp: In this function " << std::endl;
  std::cout << "INFO: TextBox:ScrollTextBoxUp: mScroll is " << args.mTextBox->getScroll() << std::endl;
  //subtract 1 from mScroll
  if ( args.mTextBox->getScroll() == 0 )
    {
    std::cout << "INFO: TextBox:ScrollTextBoxUp: first retrun, mScroll is " << args.mTextBox->getScroll() << std::endl;
    return ReturnContainer();
    }
  args.mTextBox->setScroll( args.mTextBox->getScroll() - 1 );
  std::cout << "INFO: TextBox:ScrollTextBoxUp: second return, mScroll is " << args.mTextBox->getScroll() << std::endl;
  return ReturnContainer();
}

