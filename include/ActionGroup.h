#ifndef ACTIONGROUP_H_
#define ACTIONGROUP_H_

#include <iostream>
#include <vector>
//#include <algorithm>

#include "Action.h"

class ActionGroup
{
 public:
  ActionGroup();
  virtual ~ActionGroup();
  
  void appendAction(Action *act);
  void clearAddAction(Action *act);
  Action * getAction(int element);
  void prependAction(Action *act);
  void removeAction(Action *act);

  std::vector<Action*> mActions;
  
  int getSize()
  {
    return mActions.size();
  }
  
 private:
  
};

#endif
