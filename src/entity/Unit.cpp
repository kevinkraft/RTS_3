//unit class
//
//Note:
// * The sprite renderer is set in EntityGroup

#include "Unit.h"
#include "global.h"
#include "EntityAction.h"
#include "Movement.h"
#include "FunctionCaller.h"
#include "TextLine.h"
#include "Exchange.h"
#include "Collect.h"
#include <vector>
#include "Town.h"
#include "Construct.h"

Unit::Unit(float pos_x, float pos_y, std::string name) :
  EntityAction(pos_x, pos_y, UNIT_INV_CAP)
{
  setSprite( new Sprite(pos_x, pos_y, UNIT_CLICK_WIDTH, UNIT_CLICK_HEIGHT, UNIT_CLICK_OFFSET_X, UNIT_CLICK_OFFSET_Y) );

  setPosX(pos_x);
  setPosY(pos_y);
  setName(name);

  setDead(false);

  mHunger = 0.;
}

Unit::~Unit()
{}

std::vector<FunctionCallerID> Unit::actionsByMe()
{
  std::vector<FunctionCallerID> list= EntityAction::actionsByMe();
  FunctionCaller exa = &makeExchange;
  FunctionCallerID functionID(exa, "Exchange");
  list.push_back(functionID);
  FunctionCaller coll = &makeCollect;
  FunctionCallerID functionID_coll(coll, "Collect");
  list.push_back(functionID_coll);
  FunctionCaller construct = &makeConstruct;
  FunctionCallerID functionID_construct(construct, "Construct");
  list.push_back(functionID_construct);
  return list;
}

std::vector<FunctionCallerID> Unit::actionsByMyself()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsByMyself();
  FunctionCaller move = &makeMovement;
  FunctionCallerID functionID(move, "Move");
  list.push_back(functionID);
  FunctionCaller construct = &makeConstruct;
  FunctionCallerID functionID_construct(construct, "Construct");
  list.push_back(functionID_construct);
  return list;
}

std::vector<FunctionCallerID> Unit::actionsOnMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsOnMe();
  return list;
}

std::string Unit::blurb()
{
  return "Unit: "+getName()+" #newline A unit is the main acter of the game. They are the smallest part of your empire.";
}

void Unit::dumpInventoryToStockpile()
{
  //Exchange everything in the inventory with the stockpile
  if ( getTown()->getStockpile() == nullptr )
    {
      TerminalText::printTerminal("WARN: Unit::dumpInventoryToStockpile: The Unit has no Town and/or Stockpile.");
      return;
    }
  std::vector< std::pair<int,float> > exlist = this->getInventory()->makeExhangeList();
  Exchange * ex = new Exchange(this->getTown()->getStockpile(), exlist);
  this->prependAction(ex);
}

Eat * Unit::findActionEat()
{
  Eat * eat;
  for (auto &ita: this->getActions()->mActions)
    {
      eat = dynamic_cast<Eat*>( ita );
      if ( eat != nullptr )
        return eat;
    }
  return nullptr;
}

std::vector<std::string> Unit::printStats()
{
  std::vector<std::string> rstr = this->EntityAction::printStats();
  std::vector<std::string> istr = {"Hunger:","#vspace6", makeString(getHunger()) };
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"MoveSpd.:","#vspace5",makeString(getSpeed())};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Exchng.Spd.:","#vspace2",makeString( getExchangeSpeed() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"WorkSpd.:","#vspace4",makeString( getWorkSpeed() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  return rstr;
}

void Unit::moveTo(Entity * ent)
{
  //make a move action to ent and prepends it to this Unit
  Movement * mv = new Movement(ent->getPosX(), ent->getPosY());
  this->prependAction(mv);
}

void Unit::setHunger(float h)
{
  if ( h <= 0)
    h = 0.;
  if ( h >= UNIT_MAX_HUNGER)
    h = UNIT_MAX_HUNGER;
  mHunger = h;
}

bool Unit::update()
{
  //update the state of the units hunger
  setHunger( getHunger() + UNIT_HUNGER_INCREASE );
  if ( getHunger() >= UNIT_MAX_HUNGER*3./4.)
    {
      if ( findActionEat() == nullptr)
        {
          //make the eat action as it doesnt yet exist
          TerminalText::printTerminal("INFO: Unit::update: Making the Eat action.");
          Eat * eat = new Eat();
          this->prependAction(eat);
        }
    }
  if ( getHunger() >= UNIT_MAX_HUNGER)
    {
      if ( getHP() - UNIT_HUNGER_DAMAGE <= 0.)
        TerminalText::printTerminal("INFO: Unit::update: Unit "+getName()+" has died from hunger.");
      setHP( getHP() - UNIT_HUNGER_DAMAGE );
    }

  return EntityAction::update();
}
