#ifndef ENTITYACTION_H_
#define ENTITYACTION_H_

#include <string>
#include <iostream>
#include <vector>

#include "EntityHP.h"
#include "Action.h"
#include "ActionGroup.h"
#include "ItemGroup.h"
#include "Item.h"
#include "global.h"
#include "FunctionCaller.h"

class EntityAction: public EntityHP
{
 public:

  //EntityAction(ActionGroup actionList, ItemGroup inventory);
  EntityAction(float pos_x, float pos_y, float inv_cap);
  virtual ~EntityAction();

  bool addItem(Item* item);
  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  void appendAction(Action * act);
  //void consolidateInventory();
  void clearAddAction(Action * act);
  void doAction();
  void prependAction(Action * act);
  std::vector<std::string> printInventory();
  void printInventoryTerminal();
  virtual std::vector<std::string> printStats();
  bool update();

  //are there issues with this function?
  ActionGroup * getActions()
  {
    return mActions;
  }
  double getAttackDamage()
  {
    return mAttackDamage;
  }
  //are there issues with this function?
  ItemGroup * getInventory()
  {
    return mInventory;
  }
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
  ActionGroup * mActions;
  ItemGroup * mInventory;

  //are there issues with these variables?
  double mIntrRange = UNIT_INTERACTION_RANGE;
  double mAttackDamage = UNIT_ATTACK_DAMAGE;

};

#endif
