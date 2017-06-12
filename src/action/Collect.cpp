//Collect resource action class
//
//Kevin Maguire
//02/04/2017
//

//Note:
// * The acter is set in EntityAction when the action is assigned to the acter

//-------------------------------------------------------------------------------------

//#include "Action.h"
//#include "Movement.h"
//#include "Attack.h"
//#include "Unit.h"
#include "Map.h"
//#include <cmath>
//#include "FunctionCaller.H"
#include "Collect.h"
#include "Resource.h"
#include "Building.h"
#include "Town.h"
#include "Exchange.h"
#include "TextLine.h"
#include "Region.h"

//class EntityHP;
//class EntityAction;

//-------------------------------------------------------------------------------------

Collect::Collect(Resource * target, std::string option) :
  Action()
{
  setTarget(target);
  mRepeat = true;
  mOption = option;
  mGoToNextRes = false;
}

Collect::Collect(int type, std::string option) :
  Action()
{
  //this constructor allows the Collect action to be made without specifying the Resource
  //instance to collect, just the type, Unit will Collect the nearest of given type
  mType = type;
  setTarget(nullptr);
  mRepeat = true;
  mOption = option;
  mGoToNextRes = true;
}

ReturnContainer makeCollect(ArgContainer args)
{
  Collect * coll = new Collect(args.mResource);
  ReturnContainer rcontainer = ReturnContainer();
  rcontainer.mAction = coll;
  return rcontainer;
}

Collect::~Collect()
{
  std::cout << "INFO: Collect::~Collect: Deleting Collect." << std::endl;
}

bool Collect::doAction()
{

  //search for another Resource of the same type if the Target is empty
  if ( mGoToNextRes == true )
    {
      EntityGroup * resg = mActer->getTown()->getRegion()->getEntityGroup("resources");
      Entity * close_res = nullptr;
      float dist = 0.;
      float smallest_dist = -1.;
      float type;
      if ( mTarget == nullptr )
        type = mType;
      else
        type = mTarget->getType();
      for ( auto &ent: resg->getEntities() )
        {
          //make sure its a Resource entity
          if ( dynamic_cast<Resource*>(ent) )
            {
              dist = fabs( getDistBetween(ent->getPosX(), ent->getPosY(), mActer->getPosX(), mActer->getPosY()) );
              //check if its closer and make sure its the right type Resource
              if ( (dist < smallest_dist || smallest_dist == -1.) && dynamic_cast<Resource*>(ent)->getType()==type )
                {
                  smallest_dist = dist;
                  close_res = ent;
                }
            }
        }
      if ( close_res == nullptr || dynamic_cast<Resource*>(close_res) == nullptr )
        return true; //no more resources
      else
        mTarget = dynamic_cast<Resource*>(close_res);
    }

  if ( mRepeat == false )
    return true;

  //check if the stockpile is full
  Building * sp = mActer->getTown()->getStockpile();
  if ( sp->getInventory()->getCapacity() - sp->getInventory()->getSize()  < 0.01 )
    {
      //its full, do nothing
      return false;
    }

  float aposx = mActer->getPosX();
  float aposy = mActer->getPosY();
  float tposx = mTarget->getPosX();
  float tposy = mTarget->getPosY();
  float dist = getDistBetween(aposx, aposy, tposx, tposy);
  if ( dist > mActer->getIntrRange() )
    {
      //move to the resource position
      mActer->moveTo(mTarget);
      return false;
    }

  bool unit_inv_full = false;
  bool res_empty = false;
  //make sure the Unit has enough inventory space
  //float amount = mActer->getExchangeSpeed()/10.;
  float amount = mActer->getExchangeSpeed()/1.; //for testing
  if ( mActer->getInventory()->getSize() + amount > mActer->getInventory()->getCapacity() )
    amount = mActer->getInventory()->getCapacity() - mActer->getInventory()->getSize();
  if ( amount < 0.001 )
    unit_inv_full = true;
  //make sure the resource has enough to give
  if ( mTarget->getAmount() < amount )
    {
      amount = mTarget->getAmount();
      //make sure its greater than zero
      if ( amount < 0.001 )
        {
          //resource doesn't have enough and will be deleted at update
          mTarget->setAmount(0.);
          res_empty = true;
          mGoToNextRes = true;
          //mRepeat = false;
        }
    }
  bool return_to_sp = false;
  if ( unit_inv_full == false && res_empty == false )
    {
      //make a new item and give it to the unit based on its exchange speed and take the amount from the Resource
      //check if the acter already has some of the item type
      Item * resitem = mActer->getInventory()->getItemOfType( mTarget->getType() );
      if (resitem == nullptr)
        {
          //acter does not have this item
          resitem = new Item( mTarget->getType(), amount);
          mActer->addItem( resitem );
        }
      else
        {
          //the acter already has some of this item
          resitem->setAmount( resitem->getAmount() + amount );
        }
      //remove amount from target
      mTarget->setAmount( mTarget->getAmount() - amount );
      return false;
    }
  else if ( res_empty == true )
    {
      //return to stockpile and find another res
      return_to_sp = true;
      //set target to null so it will search for another Resource
      //mRepeat = false;
      mGoToNextRes = true;
    }
  else if ( unit_inv_full == true )
    {
      //return to stockpile, exchange and repeat
      return_to_sp = true;
    }

  //return to the stockpile
  if ( mOption == "once")
    {
      //Dont return to the stockpile
      mRepeat == false;
      return true;
    }
  if ( return_to_sp == true )
    {
      //within range of the stockpile, do the exchange
      TerminalText::printTerminal("INFO: Collect::doAction: Setting up the exchange with the Stockpile.");
      Item * ret_item = mActer->getInventory()->getItemOfType( mTarget->getType() );
      if (ret_item == nullptr)
        {
          //the Resource must be empty now
          TerminalText::printTerminal("INFO: Collect::doAction: The acters Item to exchange is null, the resource must be empty. Acter: "+mActer->getName() );
          mGoToNextRes = true; //so will search for a new one
          //return true;
          return false;
        }
      Exchange * ex = new Exchange( sp, ret_item->getType(), ret_item->getAmount() );
      mActer->prependAction( ex );
      if ( mOption == "once" )
        mRepeat = false;
      return false;
    }
  else
    {
      TerminalText::printTerminal("WARN: Collect::doAction: Control flow shouldn't reach here, it should always go into the exchange action section.");
      return false;
    }

  TerminalText::printTerminal("WARN: Collect::doAction: Control flow shouldn't reach here, it should always return before this point.");
  return true;
}

void Collect::setActer(Unit * acter)
{
  mActer = acter;
}

void Collect::setActer(EntityAction * acter)
{
  Unit * unit = dynamic_cast<Unit*>(acter);
  setActer(unit);
}

