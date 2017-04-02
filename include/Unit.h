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
  std::string blurb();
  virtual std::vector<std::string> printStats();

  double getExchangeSpeed()
    {
      return mExchangeSpeed;
    }
  double getSpeed()
  {
    return mSpeed;
  }
  void setExchangeSpeed(double exspeed)
    {
      mExchangeSpeed = exspeed;
    }
  void setSpeed(double speed)
  {
    mSpeed = speed;
  }

 private:
  //std::string mName;
  double mSpeed = UNIT_SPEED;
  double mExchangeSpeed = UNIT_EXCHANGE_SPEED;

};

#endif
