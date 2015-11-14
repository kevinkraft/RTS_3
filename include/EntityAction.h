#ifndef ENTITYACTION_H_
#define ENTITYACTION_H_

#include <string>
#include <iostream>
#include <vector>

#include "EntityHP.h"
#include "Action.h"
#include "ActionGroup.h"
#include "ItemGroup.h"
#include "global.h"
#include "FunctionCaller.h"

class EntityAction: public EntityHP
{
 public:
  
  EntityAction(ActionGroup actionList, ItemGroup inventory);
  EntityAction();
  virtual ~EntityAction();

  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  void appendAction(Action * act);
  void clearAddAction(Action * act);
  void doAction();
  void prependAction(Action * act);
  bool update();

  //are there issues with this function?
  double getAttackDamage()
  {
    return mAttackDamage;
  }
  //are there issues with this function?
  double getIntrRange()
  {
    return mIntrRange;
  }
  void setAttackDamage(double attdmg)
  {
    mAttackDamage = attdmg;
  }
  void setIntrRange(double intrRange)
  {
    mIntrRange = intrRange;
  }

 private:
  ActionGroup mActions;
  ItemGroup mInventory;

  //are there issues with these variables?
  double mIntrRange = UNIT_INTERACTION_RANGE;
  double mAttackDamage = UNIT_ATTACK_DAMAGE;

};

#endif
