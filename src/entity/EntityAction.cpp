#include "EntityAction.h"
#include "EntityHP.h"
#include "ActionGroup.h"
#include "Action.h"
#include "Attack.h"
#include "InfoAction.h"
#include "ItemGroup.h"
#include "TextLine.h"
#include <vector>

//class Attack;

/*EntityAction::EntityAction(ActionGroup actionList, ItemGroup inventory) :
  EntityHP()
{
  std::cout << "EntityAction: INFO: In second constructor" << std::endl;
  //mActions = actionList;
  //mInventory = inventory;
  std::cout << "EntityAction: INFO: leaving second constructor" << std::endl;
  }*/

EntityAction::EntityAction(float pos_x, float pos_y, float inv_cap) :
  EntityHP(pos_x, pos_y)
{
  std::cout << "EntityAction: INFO: Infirst constructor" << std::endl;
  //ActionGroup actionList = ActionGroup();
  //ItemGroup inventory = ItemGroup(inv_cap);
  //EntityAction(actionList, inventory);
  mActions = ActionGroup();
  mInventory = ItemGroup(inv_cap);
}

EntityAction::~EntityAction()
{}

bool EntityAction::addItem(Item* item)
{
  std::cout << "EntityAction::addItem: INFO: Adding an Item to the ItemGroup" << std::endl;
  return mInventory.addItem(item);
}

std::vector<FunctionCallerID> EntityAction::actionsByMe()
{
  std::vector<FunctionCallerID> list;
  FunctionCaller att = &makeAttack;
  FunctionCallerID functionID(att, "Attack");
  list.push_back(functionID);
  FunctionCaller ia = &makeInfoAction;
  FunctionCallerID functionID2(ia, " Info ");
  list.push_back(functionID2);  
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
  FunctionCaller ia = &makeInfoAction;
  FunctionCallerID functionID(ia, " Info ");
  list.push_back(functionID);  
  return list;
}

void EntityAction::appendAction(Action * act)
{
  act->setActer(this);
  std::cout << "EntityAction::appendAction: INFO: After Setting acter, about to add action to the actions list" << std::endl;
  mActions.appendAction(act);  
  std::cout << "EntityAction::appendAction: INFO: Added action to the actions list" << std::endl;
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

std::vector<std::string> EntityAction::printInventory()
{
  return mInventory.print();
}

void EntityAction::printInventoryTerminal()
{
  mInventory.printTerminal();
}

std::vector<std::string> EntityAction::printStats()
{
  //make a string of the EntityAction status passes it back, to be added to a menu
  //see InfoMenu
  std::vector<std::string> rstr{"Stat:","#vspace10","Value:","#newline"};
  std::vector<std::string> istr = {"Name:","#vspace12",getName()};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"HP:","#vspace12",makeString( getHP() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Att.Dam.:","#vspace6",makeString( getAttackDamage() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Intr.Ran.:","#vspace5",makeString( getIntrRange() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"X:","#vspace13",makeString( getPosX() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Y:","#vspace13",makeString( getPosY() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  return rstr;
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
