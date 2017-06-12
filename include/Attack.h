#ifndef ATTACK_H_
#define ATTACK_H_

#include <string>
#include <iostream>

#include "Action.h"
#include "FunctionCaller.h"

//class EntityHP;
//class EntityAction;

class Attack: public Action
{
 public:

  Attack(EntityHP * target);
  virtual ~Attack();

  bool doAction();
  //void setActer(EntityAction * acter);
  // dont need to overwrite because all EntityActions should be able to attack
  // so can just override virtual setActer in Action with setActer here
  //void setActer(EntityAction * acter) override { return setActer(dynamic_cast<Unit*>(acter)); }

  EntityAction * getActer()
  {
    return mActer;
  }
  EntityHP * getTarget()
  {
    return mTarget;
  }
  void setActer(EntityAction * acter)
  {
    mActer = acter;
  }
  void setTarget(EntityHP * target)
  {
    mTarget = target;
  }

 private:
  EntityAction * mActer;
  EntityHP * mTarget;

};

ReturnContainer makeAttack(ArgContainer args);

#endif
