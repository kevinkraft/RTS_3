#include "ItemGroup.h"
#include "TextLine.h"

ItemGroup::ItemGroup(float cap)
{
  setCapacity(cap);
}

ItemGroup::~ItemGroup()
{
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      delete (*it);
    }
}

bool ItemGroup::addItem(Item* item)
{
  //check capacity
  if ( getSize() + item->getSize() < mCapacity || mCapacity == -1)
    {
      mItems.push_back(item);      
      return true;
    }
  else
    {
      std::cout << "ItemGroup::addItem: INFO: The ItemGroup is full" << std::endl;
      return false;
    }
}

float ItemGroup::getSize()
{
  float sum = 0.;
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      sum += (*it)->getSize();
    }
  return sum;
}

void ItemGroup::print()
{
  //print some of the item atributes to the terminal
  printTerminal("------------------------------------------");
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      (*it)->print();
    }
  printTerminal("------------------------------------------");
}

void ItemGroup::removeItem(Item* item)
{
  mItems.erase(std::remove(mItems.begin(), mItems.end(), item), mItems.end());
}

