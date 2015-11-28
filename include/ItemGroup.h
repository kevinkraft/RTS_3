#ifndef ITEMGROUP_H_
#define ITEMGROUP_H_

#include <iostream>
#include <vector>

#include "Item.h"

class ItemGroup
{
 public:
  ItemGroup(float cap=0.);
  virtual ~ItemGroup();
  
  bool addItem(Item * item);
  float getSize();
  void print();
  void removeItem(Item * item);  

  
  
  float getCapacity()
  {
    return mCapacity;
  }
  void setCapacity(float cap)
  {
    mCapacity = cap;
  }

  std::vector<Item*> mItems;
  
 private:
  
  float mCapacity; //-1 is no cap
  
};

#endif 
