#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

#include "FunctionCaller.h"

class Entity;
class EntityAction;
class PopMenu;


class Action
{
 public:

  Action();
  virtual ~Action();

  virtual void setActer(EntityAction * acter);

  virtual bool doAction()
  {
    std::cout << "ERROR: This action has no type." << std::endl;
    return true;
  }

};

void makeActionMenu(PopMenu * pop_menu, FunctionCallerID callerIDs, ArgContainer args);
void makeActionMenu(PopMenu * pop_menu, EntityAction * selected);
void makeActionMenu(PopMenu * pop_menu, EntityAction * selected, Entity * target, InfoMenu * info_menu, ExchangeMenu * exchange_menu);

#endif
