#include "Item.h"
#include "TextLine.h"

Item::Item(int type, float amount, float pos_x, float pos_y)
  : Selectable()
{
  setPosX(pos_x);
  setPosY(pos_y);

  mSprite = new Sprite(pos_x, pos_y);

  setType(type);
  setAmount(amount);

}

Item::~Item()
{
  std::cout << "Deleting Item" << std::endl;
}

float Item::getSize()
{
  return mAmount * mUnitSize;
}

std::vector<std::string> Item::print()
{
  //return a string with item info
  std::vector<std::string> rstr { getName()+"("+makeString(getType())+")", "#vspace10", makeString(getAmount()) };
  return rstr;
}

void Item::printTerminal()
{
  //print some atributes to the terminal
  TerminalText::printTerminal( getName() + " " + makeString(getType()) + " " + makeString(getAmount()) );
}

void Item::setType(int type)
{
  //NOTE THAT THE EXCHANGE AND COLLECT FUNCTION ARE NOT YET DESIGNED TO DEAL WITH item unit sizes GREATER THAN 1
  mType = type;
  switch (type)
    {
    case 1:
      setName("Food");
      setUnitSize(1.);
      break;
    case 2:
      setName("Wood");
      //setUnitSize(3.);
      setUnitSize(1.);
      break;
    default:
      std::cout << "Item::setType ERROR: Type Not Recognised" << std::endl;
    }
}


