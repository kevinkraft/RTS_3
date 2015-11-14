#include "EntityAction.h"
#include "EntityHP.h"
#include "ActionGroup.h"
#include "Action.h"
#include "Attack.h"
#include "ItemGroup.h"
#include <vector>

//class Attack;

EntityAction::EntityAction(ActionGroup actionList, ItemGroup inventory) :
  EntityHP()
{
  mActions = actionList;
  mInventory = inventory;
}

EntityAction::EntityAction()
{
  ActionGroup actionList = ActionGroup();
  ItemGroup inventory = ItemGroup();
  EntityAction(actionList, inventory);
}

EntityAction::~EntityAction()
{}

std::vector<FunctionCallerID> EntityAction::actionsByMe()
{
  std::vector<FunctionCallerID> list;
  FunctionCaller att = &makeAttack;
  FunctionCallerID functionID(att, "Attack");
  list.push_back(functionID);
  return list;
}

std::vector<FunctionCallerID> EntityAction::actionsByMyself()
{
  std::vector<FunctionCallerID> list;
  return list;
}

std::vector<FunctionCallerID> EntityAction::actionsOnMe()
{
  std::vector<FunctionCallerID> list = EntityHP::actionsOnMe();
  return list;
}

void EntityAction::appendAction(Action * act)
{
  act->setActer(this);
  mActions.appendAction(act);  
}

void EntityAction::clearAddAction(Action * act)
{
  if (act == nullptr)
    std::cout << "EntityAction::clearAddAction: It's a null pointer" << std::endl;
  act->setActer(this);
  mActions.clearAddAction(act);  
}

void EntityAction::doAction()
{
  if (mActions.getSize() > 0)
    {
      if (mActions.getAction(0)->doAction() == true)
	{
	  mActions.removeAction(mActions.getAction(0));
	}
    }  
}

void EntityAction::prependAction(Action * act)
{
  act->setActer(this);
  mActions.prependAction(act);  
}

bool EntityAction::update()
{
  //return false if entity is dead
  return EntityHP::update();
}
