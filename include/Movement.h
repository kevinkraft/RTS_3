#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <string>
#include <iostream>

#include "Action.h"
#include "Entity.h"
#include "EntityAction.h"
#include "Unit.h"
#include "FunctionCaller.h"


class Movement: public Action
{
 public:

  Movement(float dest_x, float dest_y);
  virtual ~Movement();

  bool doAction();
  void setActer(Unit * acter);
  //void setActer(EntityAction * acter) override { return setActer(dynamic_cast<Unit*>(acter)); }
  void setActer(EntityAction * acter);

  Unit * getActer()
  {
    return mActer;
  }
  float getDestX()
  {
    return mDest_x;
  }
  float getDestY()
  {
    return mDest_y;
  }
  void setDestX(float x)
  {
    mDest_x = x;
  }
  void setDestY(float y)
  {
    mDest_y = y;
  }

 private:
  float mDest_x;
  float mDest_y;
  Unit * mActer;
};

ReturnContainer makeMovement(ArgContainer args);
bool advanceMove(EntityAction * acter, Entity * target);

#endif
