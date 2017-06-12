#ifndef BUILDING_H_
#define BUILDING_H_

#include <string>
#include <iostream>

#include "FunctionCaller.h"
#include "EntityAction.h"

//Notes:
// * The setupType function is called in the Building constructor and when it is added
//   to an EntityGroup as the Entity constructor overwrites the Sprite

class Building: public EntityAction
{
 public:

  Building(float pos_x, float pos_y, int type);
  virtual ~Building();

  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  std::string blurb();
  virtual void setupType();

  int getType()
    {
      return mType;
    }
  void setType(int type)
  {
    mType = type;
  }

 private:
  int mType;
  //std::string mName;

};

#endif

