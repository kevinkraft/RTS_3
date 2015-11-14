#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <iostream>

#include "Sprite.h"

class Item
{
 public:
  Item(float pos_x, float pos_y, int type, int amount);
  virtual ~Item();
    
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
  bool isHeld()
  {
    return mHeld;
  }
  void setAmount(float amount)
  {
    mAmount = amount;
  }
  void setPosX(float posx)
  {
    mPos_x = posx;
  }
  void setPosY(float posy)
  {
    mPos_y = posy;
  }
  void setType(int type)
  {
    mType = type;
  }
  
 private:
  float mPos_x;
  float mPos_y;
  
  Sprite * mSprite;
  bool mHeld;
  int mType;
  float mAmount;
  
};

#endif
