#ifndef FUNCTIONCALLER_H_
#define FUNCTIONCALLER_H_

#include <string>
#include <iostream>

class Action;
class Entity;
class EntityHP;

class ArgContainer
{
 public:
  ArgContainer()
    {
      mPosX = 0.;
      mPosY = 0.;
      mSelectedEntity = nullptr;
      mTargetEntity = nullptr;
    }
  virtual ~ArgContainer()
    {}

  void setPosX(float x)
  {
    mPosX = x;
  }
  void setPosY(float y)
  {
    mPosY = y;
  }
  void setSelectedEntity(Entity * entity)
  {
    mSelectedEntity = entity;
  }
  void setTargetEntity(Entity * entity)
  {
    mTargetEntity = entity;
  }
  void setTargetEntityHP(EntityHP * entityhp)
  {
    mTargetEntityHP = entityhp;
  }

  float mPosX;
  float mPosY;
  Entity * mSelectedEntity;
  Entity * mTargetEntity;
  EntityHP * mTargetEntityHP;
  
};

class ReturnContainer
{
 public:
  ReturnContainer(int * outcome, Action * act)
    {
      mAction = act;
      mOutcome = outcome;
    }
 ReturnContainer()
   : ReturnContainer(nullptr, nullptr)
    {}
  virtual ~ReturnContainer()
    {}

  void setAction(Action * act)
    {
      mAction = act;
    }
  void setOutcome(int * b)
    {
      mOutcome = b;
    }

  Action * mAction;
  int * mOutcome;

};

typedef ReturnContainer (*FunctionCaller)(ArgContainer);
typedef std::pair<FunctionCaller, std::string> FunctionCallerID;

#endif
