#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <iostream>

#include "Sprite.h"

class Item
{
 public:
  Item(int type, int amount, float pos_x=0., float pos_y=0.);
  virtual ~Item();

  float getSize();
  void print();
  void setType(int type);
  
    
  float getAmount()
  {
    return mAmount;
  }
  std::string getName()
  {
    return mName;
  }
  float getPosX() const
  {
    return mPos_x;
  }
  float getPosY() const
  {
    return mPos_y;
  }
  Sprite * getSprite()
  {
    return mSprite;
  }
  int getType()
  {
    return mType;
  }
  float getUnitSize()
  {
    return mUnitSize;
  }
  bool isHeld()
  {
    return mHeld;
  }
  void setAmount(float amount)
  {
    mAmount = amount;
  }
  void setName(std::string name)
  {
    mName = name;
  }
  void setPosX(float posx)
  {
    mPos_x = posx;
  }
  void setPosY(float posy)
  {
    mPos_y = posy;
  }
  void setUnitSize(float usize)
  {
    mUnitSize = usize;
  }
  
 private:
  float mPos_x;
  float mPos_y;
  
  Sprite * mSprite;
  bool mHeld;
  int mType;
  float mAmount;

  float mUnitSize; //
  std::string mName;
  
};

#endif
