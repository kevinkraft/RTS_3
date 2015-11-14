#include "ItemGroup.h"

ItemGroup::ItemGroup()
{  
}

ItemGroup::~ItemGroup()
{
  for(std::vector<Item*>::iterator it = mItems.begin(); it != mItems.end(); ++it)
    {
      delete (*it);
    }
}

void ItemGroup::addItem(Item* item)
{
  mItems.push_back(item);
}

void ItemGroup::removeItem(Item* item)
{
  mItems.erase(std::remove(mItems.begin(), mItems.end(), item), mItems.end());
}

