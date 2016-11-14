//unit class
//
//Note:
// * The sprite renderer is set in EntityGroup

#include "Unit.h"
#include "global.h"
#include "EntityAction.h"
#include "Movement.h"
#include "FunctionCaller.h"

Unit::Unit(float pos_x, float pos_y, std::string name) :
  EntityAction(pos_x, pos_y, UNIT_INV_CAP)
{
  setSprite( new Sprite(pos_x, pos_y, UNIT_CLICK_WIDTH, UNIT_CLICK_HEIGHT, UNIT_CLICK_OFFSET_X, UNIT_CLICK_OFFSET_Y) );
  setPosX(pos_x);
  setPosY(pos_y);
  setName(name);
  
  setDead(false);
}

Unit::~Unit()
{}

std::vector<FunctionCallerID> Unit::actionsByMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsByMe();
  return list;
}

std::vector<FunctionCallerID> Unit::actionsByMyself()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsByMyself();
  FunctionCaller move = &makeMovement; 
  FunctionCallerID functionID(move, "Move");
  list.push_back(functionID);
  return list;
}

std::vector<FunctionCallerID> Unit::actionsOnMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsOnMe();
  return list;
}

/*std::vector<std::string> Unit::actionsByMe()
{
  std::vector<std::string> parentActions =  EntityAction::actionsByMe();
  std::vector<std::string> childActions;
  parentActions.insert( parentActions.end(), childActions.begin(), childActions.end() );
  return parentActions;
}


std::vector<std::string> Unit::actionsOnMe()
{
  std::vector<std::string> parentActions =  EntityAction::actionsOnMe();
  std::vector<std::string> childActions;
  parentActions.insert( parentActions.end(), childActions.begin(), childActions.end() );
  return parentActions;
  }*/

std::string Unit::blurb()
{
  return "Unit: "+getName()+" #newline A unit is the main acter of the game. They are the smallest part of your empire. ";
}
