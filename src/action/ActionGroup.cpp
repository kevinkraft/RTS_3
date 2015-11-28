#include "ActionGroup.h"
#include "Action.h"
#include <vector>

ActionGroup::ActionGroup()
{}

ActionGroup::~ActionGroup()
{
  for(std::vector<Action*>::iterator it = mActions.begin(); it != mActions.end(); ++it)
    {
      delete (*it);
    }
}

void ActionGroup::appendAction(Action* act)
{
  std::cout << "ActionGroup::appendAction INFO: About to add action to the action list" << std::endl;
  mActions.push_back(act);
}

void ActionGroup::clearAddAction(Action* act)
{
  mActions.clear();
  mActions.push_back(act);
}

Action * ActionGroup::getAction(int element)
{
  if (getSize() == 0)
    {
      return nullptr;
    }
  else
    {
      return mActions.at(element);
    }
}

void ActionGroup::prependAction(Action* act)
{
  mActions.insert(mActions.begin() + 0, act);
}

void ActionGroup::removeAction(Action* act)
{
  mActions.erase(std::remove(mActions.begin(), mActions.end(), act), mActions.end());
  delete act;
}

