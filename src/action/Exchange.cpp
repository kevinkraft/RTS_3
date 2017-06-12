//Exchange action class for exchanging items between inventories
//
//Kevin Maguire
//19/03/2017
//

//To Do:
// * set up base class
// * implement the working action
// * make the interface for choosing what to exchange

//Note:
// * The acter is set in EntityAction when the action is assigned to the acter

//-------------------------------------------------------------------------------------

#include "Action.h"
#include "Movement.h"
#include "Exchange.h"
//#include "Movement.h"
//#include "Unit.h"
#include "Map.h"
#include "ExchangeMenu.h"
#include <cmath>
//#include "FunctionCaller.H"
//#include "EntityAction.h"
//class EntityHP;
class EntityAction;

//-------------------------------------------------------------------------------------

Exchange::Exchange(EntityAction * target, std::vector< std::pair<int,float> > exlist)
  : Action()
{
  mExchangeMenu = nullptr;
  setTarget(target);
  setExchangeList(exlist);
}

Exchange::Exchange(EntityAction * target, int item_code, float item_amount)
  : Action()
{
  mExchangeMenu = nullptr;
  setTarget(target);
  std::vector<std::pair <int, float> > el{{item_code, item_amount}};
  setExchangeList(el);
}

Exchange::Exchange(EntityAction * target, ExchangeMenu * emenu)
  : Action()
{
  setTarget(target);
  setExchangeMenu(emenu);
}

ReturnContainer makeExchange(ArgContainer args)
{
  Exchange * ex = new Exchange(dynamic_cast<EntityAction*>(args.mTargetEntity), args.mExchangeMenu);
  ReturnContainer rcontainer = ReturnContainer();
  rcontainer.mAction = ex;
  return rcontainer;
}

Exchange::~Exchange()
{
  std::cout << "Deleting Exchange" << std::endl;
}

bool Exchange::doAction()
{
  //std::cout << "INFO: Exchange::doAction: Running Exchange." << std::endl;

  if ( mExchangeMenu != nullptr)
    {
      /*if ( mExchangeList.size() != 0 )
        {
          mExchangeMenu->wipe();
          mExchangeMenu->clear();
          mExchangeMenu->setActive(false);
          mExchangeMenu = nullptr;
          return false;
        }*/
      if ( mExchangeMenu->getFinishedSelection() == true )
        {
          mExchangeList = mExchangeMenu->getFinalExchangeList();
          mExchangeMenu->wipe();
          mExchangeMenu->clear();
          mExchangeMenu->setActive(false);
          mExchangeMenu = nullptr;
          return false;
        }
      else
        {
          //selection hasn't finished or menu isn't active
          if ( mExchangeMenu->isActive() == false )
            {
              if ( mExchangeMenu->getWasClosed() == true )
                {
                  //menu was populated but was then closed
                  mExchangeMenu->wipe();
                  mExchangeMenu->clear();
                  mExchangeMenu->setActive(false);
                  mExchangeMenu = nullptr;
                  return true;
                }
              else
                {
                  //Menu hasn't been populated
                  mExchangeMenu->populate(mActer, mTarget);
                  mExchangeMenu->setActive(true);
                  return false;
                }
            }
          return false;
        }
    }

  bool admove = advanceMove(mActer, mTarget);
  if (admove == false)
    {
      return false;
    }

  int acter_cap = mActer->getInventory()->getCapacity();
  int target_cap = mTarget->getInventory()->getCapacity();
  for ( auto &itpair : mExchangeList )
    {

      int itype = itpair.first;
      float amount = itpair.second;

      //skip if the amount is nearly zero
      if ( fabs(amount) < 0.01 )
        continue;

      //can only exchange a certain amount in each loop based on the acter exchange speed
      if ( fabs(amount) >= mActer->getExchangeSpeed())
        if ( amount > 0 )
          amount = mActer->getExchangeSpeed();
        else if ( amount < 0)
          amount = -1 * mActer->getExchangeSpeed();

      //check inventory capacity
      if ( amount + mTarget->getInventory()->getSize() > target_cap )
        {
          amount = target_cap - mTarget->getInventory()->getSize();
          itpair.second == 0; //set so the next loop will end the exchange of this item
          if ( amount == 0 )
            {
              std::cout << "WARN: Exchange::doAction: Inventory of target " << mTarget->getName() << " is at capacity. Cancelling Exchange." << std::endl;
              continue;
            }
        }
      if ( -1*amount + mActer->getInventory()->getSize() > acter_cap )
        {
          amount = -1*( acter_cap - mActer->getInventory()->getSize() );
          itpair.second == 0; //set so the next loop will end the exchange of this item
          if ( amount == 0 )
            {
              std::cout << "WARN: Exchange::doAction: Inventory of acter " << mActer->getName() << " is at capacity. Cancelling Exchange." << std::endl;
              continue;
            }
        }

      //make a new item, take it from the acter and give to target
      //need to check both as amount can be negative
      Item * acter_item = mActer->getInventory()->getItemOfType(itype);
      Item * target_item = mTarget->getInventory()->getItemOfType(itype);

      //check that the acter has enough to give
      // ADD THIS CHECK IF ITS NECESSARY

      //acter is taking, target is giving
      if ( amount < 0)
        {
          //check that the target has any to give
          if ( target_item ==  nullptr )
            {
              itpair.second = 0.;
              continue;
            }
          else
            {
              //if target doesnt have enough to give, give what it can
              if ( target_item->getAmount() < -1*amount )
                amount = -1*target_item->getAmount();
              //if target has nothing to give (nothing is defined as less than 0.01)
              if ( target_item->getAmount() - -1*amount < 0.01)
                {
                  mTarget->getInventory()->removeItem( target_item );
                }
              else
                target_item->setAmount( target_item->getAmount() - -1*amount );
              //check the acter has an item to receive, and make one if not
              if ( acter_item == nullptr )
                {
                  acter_item = new Item( itype, -1*amount);
                  mActer->addItem( acter_item );
                }
              else
                acter_item->setAmount( acter_item->getAmount() + -1*amount );
              itpair.second = itpair.second - amount;
            }
        }
      //acter is giving, target is taking
      if ( amount > 0)
        {
          //if the actor has nothing to give
          if ( acter_item == nullptr )
            {
              itpair.second = 0;
              continue;
            }
          else
            {
              //if the acter doesnt have enough to give
              if ( acter_item->getAmount() < amount )
                amount = acter_item->getAmount();
              if ( acter_item->getAmount() - amount < 0.01)
                {
                  mActer->getInventory()->removeItem( acter_item );
                }
              else
                acter_item->setAmount( acter_item->getAmount() - amount );
              //check the target has an item to receive, and make one if not
              if ( target_item == nullptr )
                {
                  target_item = new Item( itype, amount);
                  mTarget->addItem( target_item );
                }
              else
                target_item->setAmount( target_item->getAmount() + amount );
              itpair.second = itpair.second - amount;
            }
        }

      return false;
    }

  //finished
  return true;
}

void Exchange::setActer(EntityAction * acter)
{
  std::cout << "INFO: Exchange::setActer: Setting Acter" << std::endl;
  Unit * unit_acter = dynamic_cast<Unit*>(acter);
  mActer = unit_acter;
}
