#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

//#include <string>
//#include <iostream>
//#include <vector>

#include "Action.h"
#include "Unit.h"
//#include "FunctionCaller.h"
#include "Construction.h"

//class EntityHP;
//class EntityAction;

class Construct: public Action
{
 public:

  Construct(Construction * target);
  Construct(int building_type);
  virtual ~Construct();

  bool doAction();
  void setActer(EntityAction * acter);

  Unit * getActer()
  {
    return mActer;
  }
  Construction * getTarget()
  {
    return mTarget;
  }
  void setTarget(Construction * target)
  {
    mTarget = target;
  }

 private:

  Unit * mActer;
  Construction * mTarget;
  int mType;

};

ReturnContainer makeConstruct(ArgContainer args);

#endif
