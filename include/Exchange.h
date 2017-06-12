#ifndef EXCHANGE_H_
#define EXCHANGE_H_

//#include <string>
//#include <iostream>
#include <vector>

#include "Action.h"
#include "Unit.h"
//#include "FunctionCaller.h"

//class EntityHP;
//class EntityAction;

class Exchange: public Action
{
 public:

  Exchange(EntityAction * target, std::vector< std::pair<int,float> > exlist);
  Exchange(EntityAction * target, int item_code, float item_amount);
  Exchange(EntityAction * target, ExchangeMenu * exmenu);
  virtual ~Exchange();

  bool doAction();
  void setActer(EntityAction * acter);

  Unit * getActer()
  {
    return mActer;
  }
  std::vector< std::pair<int,float> > getExchangeList()
  {
    return mExchangeList;
  }
  ExchangeMenu * getExchangeMenu()
  {
    return mExchangeMenu;
  }
  EntityAction * getTarget()
  {
    return mTarget;
  }
  void setExchangeList(std::vector< std::pair<int,float> > el)
  {
    mExchangeList = el;
  }
  void setExchangeMenu(ExchangeMenu * em)
  {
    mExchangeMenu = em;
  }
  void setTarget(EntityAction * target)
  {
    mTarget = target;
  }

 private:

  Unit * mActer;
  EntityAction * mTarget;
  std::vector< std::pair<int,float> > mExchangeList;
  ExchangeMenu * mExchangeMenu;

};

ReturnContainer makeExchange(ArgContainer args);

#endif
