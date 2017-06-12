#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <iostream>

#include "Entity.h"
#include "EntityGroup.h"

//Notes:
// * The setupType function is called in the Resource constructor and when it is added
//   to an EntityGroup as the Entity constructor overwrites the Sprite

class Resource: public Entity
{
 public:

  Resource(float pos_x, float pos_y, int type, float amount=100);
  virtual ~Resource();

  virtual std::vector<FunctionCallerID> actionsOnMe();
  //using Entity::setImage;
  std::string blurb();
  std::vector<std::string> printStats();
  void setupType();
  bool update();

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
  //std::string mName;

};

void placeUniformResources(EntityGroup * Resources, int type, int number, int xlow, int ylow, int xhigh, int yhigh, int seed);
void placeGroupedResources(EntityGroup * Resources, int type, int group_number, int maxgroup, float group_delta, int xlow, int ylow, int xhigh, int yhigh, int seed);

#endif
