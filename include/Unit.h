#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include <iostream>


#include "EntityAction.h"
#include "global.h"
#include "FunctionCaller.h"

class Unit: public EntityAction
{
 public:
  
  Unit(float pos_x, float pos_y, std::string name = "NAME");
  virtual ~Unit();

  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  
  std::string getName()
    {
      return mName;
    }
  double getSpeed()
  {
    return mSpeed;
  }
  void setName(std::string name)
  {
    mName = name;
  }
  void setSpeed(double speed)
  {
    mSpeed = speed;
  }
  
 private:
  std::string mName;
  double mSpeed = UNIT_SPEED;
  
};

#endif
