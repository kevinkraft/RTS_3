//Attack action class
//
//Kevin Maguire
//15/08/2015
//

//To Do:
// * When the Building class exists I will have to have two separate doAttack for unit
//   and building as unit can move and buidling can't

//Note:
// * The acter is set in EntityAction when the action is assigned to the acter

//-------------------------------------------------------------------------------------

#include "Action.h"
#include "Movement.h"
#include "Attack.h"
#include "Unit.h"
#include "Map.h"
#include <cmath>
#include "FunctionCaller.H"

class EntityHP;
//class EntityAction;

//-------------------------------------------------------------------------------------

Attack::Attack(EntityHP * target) :
  Action()
{
  setTarget(target);
}

ReturnContainer makeAttack(ArgContainer args)
{
  Attack * att = new Attack(args.mTargetEntityHP);
  ReturnContainer rcontainer = ReturnContainer();
  rcontainer.mAction = att;
  return rcontainer;
}

Attack::~Attack()
{
  std::cout << "Deleting Attack" << std::endl;
}

bool Attack::doAction()
{
  float aposx = mActer->getPosX();
  float aposy = mActer->getPosY();
  float tposx = mTarget->getPosX();
  float tposy = mTarget->getPosY();
  float dist = getDistBetween(aposx, aposy, tposx, tposy);

  std::cout << "Attack::doAction: INFO: mTarget->getHP(): " << mTarget->getHP() << std::endl;

  bool admove = advanceMove(mActer, mTarget);
  if (admove == false)
    {
      //if it isnt close enough advance towards and go to next loop
      return false;
    }
  /*if (std::abs(dist) > mActer->getIntrRange())
    {
      //move a quarter of the distance to the target
      return advanceMove(mActer, mTarget);
      //Movement * move = new Movement( aposx - (aposx - tposx)/4., aposy - (aposy - tposy)/4. );
      //mActer->prependAction(move);
      //return false;
    }*/
  if (std::abs(dist) <= mActer->getIntrRange())
    {
      //within range
      if ( mTarget->isDead() )
        return true;
      else
        {
          mTarget->setHP( mTarget->getHP() - mActer->getAttackDamage() );
          return false;
        }
    }
  std::cout << "Attack::doAction: ERROR: Invalid distance between objets." << std::endl;
  return true;
}



