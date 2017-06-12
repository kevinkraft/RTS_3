#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include <iostream>


#include "EntityAction.h"
#include "global.h"
#include "FunctionCaller.h"
#include "Eat.h"

class Unit: public EntityAction
{
 public:

  Unit(float pos_x, float pos_y, std::string name = "NAME");
  virtual ~Unit();

  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  std::string blurb();
  void dumpInventoryToStockpile();
  Eat * findActionEat();
  void moveTo(Entity * ent);
  virtual std::vector<std::string> printStats();
  void setHunger(float h);
  bool update();

  double getExchangeSpeed()
    {
      return mExchangeSpeed;
    }
  float getHunger()
  {
    return mHunger;
  }
  double getSpeed()
  {
    return mSpeed;
  }
  double getWorkSpeed()
  {
    return mWorkSpeed;
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

  double mSpeed = UNIT_SPEED;
  double mExchangeSpeed = UNIT_EXCHANGE_SPEED;
  //EntityAction * mStockpile;
  float mHunger;
  float mWorkSpeed = UNIT_WORK_SPEED;

};

#endif
