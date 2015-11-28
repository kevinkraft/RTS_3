//Movement action class
//
//Kevin Maguire
//09/08/2015
//

//Note:
// * The acter is set in EntityAction when the action is assigned to the acter

//-------------------------------------------------------------------------------------

#include "Action.h"
#include "Movement.h"
#include "Unit.h"
#include <cmath>
#include "FunctionCaller.h"

//-------------------------------------------------------------------------------------

Movement::Movement(float dest_x, float dest_y) :
  Action()
{  
  //setActer(acter);
  setDestX(dest_x);
  setDestY(dest_y);
}

ReturnContainer makeMovement(ArgContainer args) 
{
  Movement * move = new Movement(args.mPosX, args.mPosY);
  ReturnContainer rcontainer = ReturnContainer();
  rcontainer.mAction = move;
  return rcontainer;
}

Movement::~Movement()
{
  //std::cout << "Deleting Movement" << std::endl;
}

bool Movement::doAction()
{
  if (mActer->getPosX() != mDest_x)
    {
      if (std::abs(mActer->getPosX() - mDest_x) < mActer->getSpeed())
	{
	  mActer->setPosX(mDest_x);
	}
      else if (mActer->getPosX() > mDest_x)
	{
	  mActer->setPosX(mActer->getPosX() - mActer->getSpeed());
	}
      else if (mActer->getPosX() < mDest_x)
	{
	  mActer->setPosX(mActer->getPosX() + mActer->getSpeed());
	}
      return false;
    }
  else if (mActer->getPosY() != mDest_y)
    {
      if (std::abs(mActer->getPosY() - mDest_y) < mActer->getSpeed())
	{
	  mActer->setPosY(mDest_y);
	}
      else if (mActer->getPosY() > mDest_y)
	{
	  mActer->setPosY(mActer->getPosY() - mActer->getSpeed());
	}
      else if (mActer->getPosY() < mDest_y)
	{
	  mActer->setPosY(mActer->getPosY() + mActer->getSpeed());
	}
      return false;
    }
  else 
    {
      std::cout << "Movement:doAction: INFO: Final x pos: " << mActer->getPosX() << std::endl;   
      std::cout << "Movement:doAction: INFO: Final y pos: " << mActer->getPosY() << std::endl;   
      std::cout << "INFO: Finished Moving, leaving Movement::doAction" << std::endl;   
      return true;
    }
}

void Movement::setActer(Unit * acter)
{
  std::cout << "In Movement, setting acter." << std::endl;
  mActer = acter;
  std::cout << "In Movement, after setting acter." << std::endl;
}

void Movement::setActer(EntityAction * acter)
{
  std::cout << "In Movement with EntityAction, setting acter." << std::endl;
  Unit * unit_acter = dynamic_cast<Unit*>(acter);
  setActer(unit_acter);
}



