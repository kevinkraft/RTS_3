#include<algorithm>
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
      mItems.push_back( item );
      return true;
    }
  else
    {
      std::cout << "ItemGroup::addItem: INFO: The ItemGroup is full" << std::endl;
      return false;
    }
}

/*void ItemGroup::consolidate()
{
  std::vector<Item*>::iterator item = mItems.begin();
  for(; item != mItems.end(); item++)
  {
    for( std::vector<Item*>::iterator itemin = item; itemin != mItems.end(); itemin++)
    {
      if (itemin == item) continue;
      item->setAmount( itemin->getAmount()+item->getAmount() );
    }

  }


}*/

float ItemGroup::getSize()
{
  float sum = 0.;
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      sum += (*it)->getSize();
    }
  return sum;
}

Item* ItemGroup::getItemOfType(int itype)
{
  for (auto &item: mItems)
    if ( item->getType() == itype) return item;
  return nullptr;
}

std::vector<std::string> ItemGroup::print()
{
  //make a string of the items and pass it back, to be added to a menu
  //see InfoMenu
  std::vector<std::string> rstr{"Item","#vspace10","Amount","#newline"};
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      std::vector<std::string> istr = (*it)->print();
      rstr.insert( rstr.end(), istr.begin(), istr.end() );
      rstr.push_back("#newline");
    }
  return rstr;
}

void ItemGroup::printTerminal()
{
  //print some of the item atributes to the terminal
  TerminalText::printTerminal("------------------------------------------");
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      (*it)->printTerminal();
    }
  TerminalText::printTerminal("------------------------------------------");
}

void ItemGroup::removeItem(Item* item)
{
  //if ( mItems.size() == 1 )
  //  mItems == nullptr;
  //else
    mItems.erase(std::remove(mItems.begin(), mItems.end(), item), mItems.end());
}

