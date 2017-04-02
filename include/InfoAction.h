//Class to call the InfoMenu function as an action
//
//Kevin Maguire
//24/07/16
//

//Note:
// * This isn't really an action but this is the best way for the Info option to
//   appear in the pop_menu

//-------------------------------------------------------------------------------------

#ifndef INFOACTION_H_
#define INFOACTION_H_

#include <string>
#include <iostream>

//#include "Action.h"
#include "FunctionCaller.h"
#include "Resource.h"

//class EntityHP;
//class EntityAction;

//-------------------------------------------------------------------------------------

class InfoAction: public Action
{
 public:

  InfoAction(Entity * target, InfoMenu * info_menu);
  //InfoAction(EntityAction * target);
  InfoAction(Resource * target);
  virtual ~InfoAction();

  bool doAction();

  InfoMenu * getInfoMenu()
  {
    return mInfoMenu;
  }
  Entity * getTarget()
  {
    return mTarget;
  }
  void setInfoMenu(InfoMenu * info_menu)
  {
    mInfoMenu = info_menu;
  }
  void setTarget(Entity * target)
  {
    mTarget = target;
  }

  InfoMenu * mInfoMenu;

 private:
  Entity * mTarget;

};

ReturnContainer makeInfoAction(ArgContainer args);

#endif
