#ifndef ENTITYHP_H_
#define ENTITYHP_H_

#include <string>
#include <iostream>

#include "Entity.h"
#include "global.h"

class EntityHP: public Entity
{
 public:
  
  EntityHP(float HP = UNIT_HP);
  virtual ~EntityHP();
  virtual bool update();

  virtual std::vector<FunctionCallerID> actionsOnMe();
  
  float getHP()
  {
    return mHP;
  }
  void setHP(float HP)
  {
    mHP = HP;
  }
  
 private:
  float mHP;

};

#endif
