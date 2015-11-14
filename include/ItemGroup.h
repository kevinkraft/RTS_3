#ifndef ITEMGROUP_H_
#define ITEMGROUP_H_

#include <iostream>
#include <vector>
//#include <algorithm>

#include "Item.h"

class ItemGroup
{
 public:
  ItemGroup();
  virtual ~ItemGroup();
  
  void addItem(Item * item);
  void removeItem(Item * item);  
  //void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  
  std::vector<Item*> mItems;
  
 private:
  
};

#endif 
