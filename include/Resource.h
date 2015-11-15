#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <iostream>

#include "Entity.h"
#include "EntityGroup.h"

class Resource: public Entity
{
 public:
  
  Resource(float pos_x, float pos_y, int type, float amount);
  virtual ~Resource();

  virtual std::vector<FunctionCallerID> actionsOnMe();
  using Entity::setImage;
  void setImage();

  float getAmount()
  {
    return mAmount;
  }
  int getType()
  {
    return mType;
  }
  void setAmount(float amount)
  {
    mAmount = amount;
  }
  void setType(int type)
  {
    mType = type;
  }
  
 private:

  int mType;
  float mAmount;
  
};

void placeResources(EntityGroup * Resources, int type, int amount);

#endif
