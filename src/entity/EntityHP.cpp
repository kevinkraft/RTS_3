#include "EntityHP.h"
#include "global.h"
#include "Attack.h"

EntityHP::EntityHP(float HP) :
  Entity()
{
  setHP(HP);
}

EntityHP::~EntityHP()
{}

std::vector<FunctionCallerID> EntityHP::actionsOnMe()
{
  std::vector<FunctionCallerID> list;
  FunctionCaller att = &makeAttack; 
  FunctionCallerID functionID(att, "Attack");
  list.push_back(functionID);
  return list;
}

bool EntityHP::update()
{
  if (getHP() <= 0.)
    {
      setDead(true);
    }
  return Entity::update();
}
