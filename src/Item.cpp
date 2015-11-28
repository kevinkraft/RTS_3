#include "Item.h"
#include "Message.h"

Item::Item(int type, int amount, float pos_x, float pos_y)
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

void Item::print()
{
  //print some atributes to the terminal
  printTerminal( getName() + " " + makeString(getType()) + " " + makeString(getAmount()) );
}

void Item::setType(int type)
{
  mType = type;
  switch (type)
    {
    case 1:
      setName("Food");
      setUnitSize(1.);
      break;
    case 2:
      setName("Wood");
      setUnitSize(3.);
      break;
    default:
      std::cout << "Item::setType ERROR: Type Not Recognised" << std::endl;
    }
}


