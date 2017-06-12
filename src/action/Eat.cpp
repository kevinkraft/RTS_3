//#include "Action.h"
//#include "Movement.h"
//#include "Attack.h"
//#include "Unit.h"
//#include "Map.h"
//#include <cmath>
//#include "FunctionCaller.H"
#include "Eat.h"
#include "Unit.h"
#include "Building.h"
#include "Town.h"
#include "Exchange.h"
#include "Region.h"
#include "TextLine.h"
#include "Resource.h"
#include "Collect.h"

//class EntityHP;
//class EntityAction;

//-------------------------------------------------------------------------------------

Eat::Eat()
  : Action()
{
}

Eat::~Eat()
{
  //std::cout << "INFO: Eat::~Eat: Deleting Eat." << std::endl;
}

bool Eat::doAction()
{
  bool go_collect = false;
  //how much food is needed to make the hunger zero
  float food_needed = mActer->getHunger() / ( -1. * FOOD_HUNGER_VALUE );

  //check if there is food in the inventory
  Item * fitem = mActer->getInventory()->getItemOfType(1);
  if ( fitem != nullptr )
    {
      //TerminalText::printTerminal("INFO: Eat::doAction: The unit has some food");
      //acter has some food
      float eat_amount = food_needed;
      //Does the food item have enough
      if ( fitem->getAmount() < food_needed )
        eat_amount = fitem->getAmount();

      //remove amount from the item
      if ( fitem->getAmount() - eat_amount < 0.01 )
        {
          fitem->setAmount(0);
          mActer->getInventory()->removeItem(fitem);
          delete fitem;
        }
      else
        fitem->setAmount( fitem->getAmount() - eat_amount );

      //remove hunger from the acter
      mActer->setHunger( mActer->getHunger() + eat_amount*FOOD_HUNGER_VALUE );

      return true;
    }
  else
    {
      //TerminalText::printTerminal("INFO: Eat::doAction: The unit does NOT have any food");
      //the acter doesn't have any food

      //check if the Unit inventory is full
      if ( mActer->getInventory()->getFreeSpace() == 0.)
        {
          //dump everything to the stockpile so there is space for food
          mActer->dumpInventoryToStockpile();
          return false;
        }

      //check the stockpile for food
      Building * sp = mActer->getTown()->getStockpile();
      if ( sp != nullptr )
        { //the town has a stockpile
          //TerminalText::printTerminal("INFO: Eat::doAction: Checking the stockpile for food.");
          Item * stock_item = sp->getInventory()->getItemOfType(1);
          if ( stock_item != nullptr)
            {
              //TerminalText::printTerminal("INFO: Eat::doAction: The stockpile has some food.");
              //the stockpile has some food, go exchange it
              //TerminalText::printTerminal("INFO: Eat::doAction: The Unit needs "+makeString(food_needed)+" food.");
              Exchange * exc = new Exchange(sp, 1, -1*food_needed);
              mActer->prependAction(exc);
              return false;
            }
          else
            {
              //TerminalText::printTerminal("INFO: Eat::doAction: The stockpile has no food");
              go_collect = true;
            }
        }
      else //the town has no stockpile
        {
          //TerminalText::printTerminal("INFO: Eat::doAction: The stockpile has no food as it doesn't exist.");
          go_collect = true;
        }
    }

  if ( go_collect = true )
    {
      //TerminalText::printTerminal("INFO: Eat::doAction: The Unit is going to collect food.");
      //go to the nearest resource and collect some food
      //find the nearest one
      EntityGroup * resg = mActer->getTown()->getRegion()->getEntityGroup("resources");
      Entity * close_res = nullptr;
      float dist = 0.;
      float smallest_dist = -1.;
      for ( auto &ent: resg->getEntities() )
        {
          //make sure its a Resource entity
          if ( dynamic_cast<Resource*>(ent) )
            {
              dist = fabs( getDistBetween(ent->getPosX(), ent->getPosY(), mActer->getPosX(), mActer->getPosY()) );
              //check if its closer and make sure its a food Resource
              if ( (dist < smallest_dist || smallest_dist == -1.) && dynamic_cast<Resource*>(ent)->getType()==1 )
                {
                  smallest_dist = dist;
                  close_res = ent;
                }
            }
        }
      if ( close_res != nullptr)
        {
          //make the Collect action
          Collect * col = new Collect(dynamic_cast<Resource*>(close_res), "once"); //only do one collect cycle
          mActer->prependAction(col);
          return false;
        }
    }

  //starve
  return true;
}

void Eat::setActer(EntityAction * acter)
{
  std::cout << "INFO: Exchange::setActer: Setting Acter" << std::endl;
  Unit * unit_acter = dynamic_cast<Unit*>(acter);
  mActer = unit_acter;
}


