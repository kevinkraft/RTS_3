#ifndef ARGCONTAINER_H_
#define ARGCONTAINER_H_

#include <string>
#include <iostream>

//#include "Menu.h"

class Menu;
class Action;
class Entity;
class EntityHP;
class TextBox;

class ArgContainer
{
 public:
  ArgContainer()
    {
      mPosX = 0.;
      mPosY = 0.;
      mSelectedEntity = nullptr;
      mTargetEntity = nullptr;
      mMenu = nullptr;
      mTextBox = nullptr;
    }
  virtual ~ArgContainer()
    {}
  
  void setMenu(Menu * m)
  {
    mMenu = m;
  }
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
  Menu * mMenu;
  TextBox * mTextBox;

};

class ReturnContainer
{
 public:
  ReturnContainer(int outcome, Action * act)
    {
      mAction = act;
      mOutcome = outcome;
    }
 ReturnContainer()
   : ReturnContainer(0, nullptr)
    {}
  virtual ~ReturnContainer()
    {}

  void setAction(Action * act)
    {
      mAction = act;
    }
  void setOutcome(int b)
    {
      mOutcome = b;
    }

  Action * mAction;
  int mOutcome;

};

#endif
