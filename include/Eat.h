//The Eat class
//
//Kevin Maguire
//08/04/17
//

//Notes:
// * This is an automatic action, thus it cant be chosen by the user,
//   does not appear in the PopMenu and doesn't need to appear in the
//   Entity::actionBy... functions.
// * For now I will allow Eat to be an instantaneous action

//---------------------------------------------------------------------

#ifndef EAT_H_
#define EAT_H_

//#include <string>
//#include <iostream>

#include "Action.h"
//#include "FunctionCaller.h"

//class EntityHP;
//class EntityAction;
class Unit;

//---------------------------------------------------------------------

class Eat: public Action
{
 public:

  Eat();
  virtual ~Eat();

  bool doAction();
  void setActer(EntityAction * acter);

 private:
  Unit * mActer;

};

ReturnContainer makeEat(ArgContainer args);

#endif
