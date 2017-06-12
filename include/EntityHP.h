#ifndef ENTITYHP_H_
#define ENTITYHP_H_

#include <string>
#include <iostream>

#include "Entity.h"
#include "global.h"
//#include "Town.h"

class Town;

class EntityHP: public Entity
{
 public:

  EntityHP(float pos_x, float pos_y, float HP = UNIT_HP);
  virtual ~EntityHP();
  virtual bool update();

  virtual std::vector<FunctionCallerID> actionsOnMe();

  float getHP()
  {
    return mHP;
  }
  Town * getTown()
  {
    return mTown;
  }
  void setHP(float HP)
  {
    mHP = HP;
  }
  void setTown(Town * town)
  {
    mTown = town;
  }

 private:
  float mHP;

  Town * mTown;

};

#endif
