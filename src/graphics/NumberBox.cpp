//#include <string>
//#include <sstream>
//#include <vector>
//#include <regex>

//#include "TextBox.h"
//#include "Menu.h"
//#include "texture.h"
//#include "global.h"
#include "NumberBox.h"

NumberBox::NumberBox(float minval, float maxval, float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent)
 : DisplayPiece(parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent),
 SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
{
  //dont forget to reset the positions or you'll be using the wrong display piece
  setParent(parent);
  setRelX(rel_x);
  setRelY(rel_y);
  setRelHeight(rel_h);
  setRelWidth(rel_w);
  setPositions();

  setMin(minval);
  setMax(maxval);
  setValue();
  setup();
}

NumberBox::~NumberBox()
{
  std::cout << "Deleting NumberBox" << std::endl;
}

void NumberBox::setup()
{
  //make a textline to display the number
  TextLine * tl = new TextLine( getPosX() + 0.55*getPosX(), getPosY() + 0.1*getPosY(), 0.35*getWidth(), 0.35*getHeight(), makeString(mValue), this->mTextMaker);
  this->addTextLine(tl);
  //make the 4 buttons
  ArgContainer args = ArgContainer();
  args.setMenu(this);
  Button * bt_plus1 = new Button(120., 45., 0.3, 0.3, "->", &incrementValueByOne, args, this);
  this->addButton( bt_plus1 );
  Button * bt_minus1 = new Button(20., 45., 0.3, 0.3, "<-", &decrementValueByOne, args, this);
  this->addButton( bt_minus1 );
  Button * bt_plusmore = new Button(110., 80., 0.35, 0.25, "->>", &incrementValueByTen, args, this);
  this->addButton( bt_plusmore );
  Button * bt_minusmore = new Button(20., 80., 0.35, 0.25, "<<-", &decrementValueByTen, args, this);
  this->addButton( bt_minusmore );
}

void NumberBox::setValue()
{
  //set to zero or the median of the given range
  if ( mMin <= 0 and mMax >= 0)
    setValue(0.);
  else
    setValue( (mMax - mMin) / 2. );
  return;
}

void NumberBox::setValue(float vl)
{
  mValue = vl;
  std::cout << "INFO: NumberBox::setValue: " << mValue << std::endl;
  if ( mTextLines.size() == 1)
    {
      mTextLines[0]->setText( makeString(mValue) );
    }
}

//----------------------------------------------------------------------------------------------------------
// Other Functions
//----------------------------------------------------------------------------------------------------------

ReturnContainer incrementValueByOne(ArgContainer args)
{
  std::cout << "INFO: NumberBox:incrementValueByOne: In this function." << std::endl;
  ReturnContainer rcont = ReturnContainer();
  NumberBox * nb = dynamic_cast<NumberBox*>(args.mMenu);
  if ( nb == nullptr )
    {
      std::cout << "ERRO: NumberBox:incrementValueByOne: The menu in the args is not a NumberBox class instance." << std::endl;
      return rcont;
    }
  if ( nb->getValue() + 1. < nb->getMax() )
    nb->setValue( nb->getValue() + 1. );
  else
    nb->setValue( nb->getMax() );
  return rcont;
}

ReturnContainer decrementValueByOne(ArgContainer args)
{
  std::cout << "INFO: NumberBox:decrementValueByOne: In this function." << std::endl;
  ReturnContainer rcont = ReturnContainer();
  NumberBox * nb = dynamic_cast<NumberBox*>(args.mMenu);
  if ( nb == nullptr )
    {
      std::cout << "ERRO: NumberBox:decrementValueByOne: The menu in the args is not a NumberBox class instance." << std::endl;
      return rcont;
    }
  if ( nb->getValue() - 1. > nb->getMin() )
    nb->setValue( nb->getValue() - 1. );
  else
    nb->setValue( nb->getMin() );
  return rcont;
}

ReturnContainer incrementValueByTen(ArgContainer args)
{
  std::cout << "INFO: NumberBox:incrementValueByTen: In this function." << std::endl;
  ReturnContainer rcont = ReturnContainer();
  NumberBox * nb = dynamic_cast<NumberBox*>(args.mMenu);
  if ( nb == nullptr )
    {
      std::cout << "ERRO: NumberBox:incrementValueByTen: The menu in the args is not a NumberBox class instance." << std::endl;
      return rcont;
    }
  if ( nb->getValue() + 10. < nb->getMax() )
    nb->setValue( nb->getValue() + 10. );
  else
    nb->setValue( nb->getMax() );
  return rcont;
}

ReturnContainer decrementValueByTen(ArgContainer args)
{
  std::cout << "INFO: NumberBox:decrementValueByTen: In this function." << std::endl;
  ReturnContainer rcont = ReturnContainer();
  NumberBox * nb = dynamic_cast<NumberBox*>(args.mMenu);
  if ( nb == nullptr )
    {
      std::cout << "ERRO: NumberBox:decrementValueByTen: The menu in the args is not a NumberBox class instance." << std::endl;
      return rcont;
    }
  if ( nb->getValue() - 10. > nb->getMin() )
    nb->setValue( nb->getValue() - 10. );
  else
    nb->setValue( nb->getMin() );
  return rcont;
}

