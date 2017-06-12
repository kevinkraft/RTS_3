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
  //void consolidate();
  std::vector< std::pair<int,float> > makeExhangeList();
  float getFreeSpace();
  float getSize();
  Item * getItemOfType(int itype);
  std::vector<std::string> print();
  void printTerminal();
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
