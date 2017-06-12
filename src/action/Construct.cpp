//Construct action class for running Constructions to make Buildings
//
//Kevin Maguire
//16/04/2017
//

//-------------------------------------------------------------------------------------

//#include "Action.h"
//#include "Movement.h"
#include "Construct.h"
//#include "Map.h"
//#include "ExchangeMenu.h"
//#include <cmath>
//class EntityAction;
#include "Exchange.h"
#include "Building.h"
#include "Town.h"
#include "Collect.h"
#include "TextLine.h"

//-------------------------------------------------------------------------------------

Construct::Construct(Construction * target)
  : Action()
{
  mTarget = target;
  mType == mTarget->getType();
}

Construct::Construct(int building_type)
  : Action()
{
  mTarget == nullptr;
  mType = building_type;
}

ReturnContainer makeConstruct(ArgContainer args)
{
  ReturnContainer rcontainer = ReturnContainer();
  if ( args.mConstruction == nullptr )
    {
      //need to make a Construction Entity
      // NOT YET IMPLEMENTED

    }
  else
    {
      //dont need to make a construction entity
      Construct * ct = new Construct( args.mConstruction );
      rcontainer.mAction = ct;
    }
  return rcontainer;
}

Construct::~Construct()
{
  std::cout << "Construct::~Construct: Deleting Construct." << std::endl;
}

bool Construct::doAction()
{

  //Does the Construction need items?
  if ( mTarget->needsMaterials() == true)
    {
      //the construction needs materials
      std::pair<int,float> needed_mats = mTarget->nextItemNeeded();
      float exchange_amount = needed_mats.second;

      //see if the Unit has some of this item
      Item * units_item = mActer->getInventory()->getItemOfType(needed_mats.first);
      if ( units_item != nullptr )
        {
          //the unit has some of this item
          //how much can/should be exchanged? This is probably unnecessary as its handled by Exchange,
          //but its no harm to make sure, might avoid problems later
          if ( needed_mats.second > units_item->getAmount() )
            exchange_amount = units_item->getAmount();
          else if ( needed_mats.second < units_item->getAmount() )
            exchange_amount = needed_mats.second;
          //make the exchange action
          Exchange * ex = new Exchange( mTarget, needed_mats.first, exchange_amount);
          mActer->prependAction(ex);
          return false;
        }
      else
        {
          //the unit does not have any of this item
          //Does the stockpile have some?
          Building * sp = mActer->getTown()->getStockpile();
          Item * sp_item = sp->getInventory()->getItemOfType(needed_mats.first);
          if (sp_item != nullptr )
            {
              //the stockpile has some of this item
              //How much does it have/ how much can the Unit carry?
              if ( sp_item->getAmount() < exchange_amount )
                exchange_amount = sp_item->getAmount();
              if ( exchange_amount > mActer->getInventory()->getFreeSpace() )
                exchange_amount = mActer->getInventory()->getFreeSpace();
              //make an exchange with the stockpile
              Exchange * ex = new Exchange( mTarget, needed_mats.first, exchange_amount);
              mActer->prependAction(ex);
              return false;
            }
          else
            {
              //the stockpile has none of this item
              //go and collect this item
              Collect * col = new Collect(needed_mats.first, "once");
              mActer->prependAction(col);
              return false;
            }
        }

    }
  else
    {
      //the construction doesn't need materials
      //Do work
      if ( mTarget->getWork() <= 0.)
        return true;
      mTarget->setWork( mTarget->getWork() - mActer->getWorkSpeed() );
      return false;
    }
  TerminalText::printTerminal("WARN: Construct::doAction: Control flow should not reach here.");
  return true;
}

void Construct::setActer(EntityAction * acter)
{
  std::cout << "INFO: Construct::setActer: Setting Acter" << std::endl;
  Unit * unit_acter = dynamic_cast<Unit*>(acter);
  mActer = unit_acter;
}
