#ifndef COLLECT_H_
#define COLLECT_H_

//#include <string>
//#include <iostream>

#include "Action.h"
#include "Unit.h"
//#include "FunctionCaller.h"

//class EntityHP;
//class EntityAction;

class Collect: public Action
{
 public:

  Collect(Resource * target, std::string option = "");
  Collect(int type, std::string option = "");
  virtual ~Collect();

  bool doAction();
  void setActer(Unit * acter);
  void setActer(EntityAction * acter);

  Unit * getActer()
  {
    return mActer;
  }
  Resource * getTarget()
  {
    return mTarget;
  }

  void setTarget(Resource * target)
  {
    mTarget = target;
  }

 private:
  Unit * mActer;
  Resource * mTarget;
  bool mRepeat;
  std::string mOption;
  bool mGoToNextRes;
  int mType;

};

ReturnContainer makeCollect(ArgContainer args);

#endif
