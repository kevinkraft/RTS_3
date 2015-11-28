#ifndef BUILDING_H_
#define BUILDING_H_

#include <string>
#include <iostream>

#include "FunctionCaller.h"
#include "EntityAction.h"

class Building: public EntityAction
{
 public:
  
  Building(float pos_x, float pos_y, int type);
  virtual ~Building();
  
  virtual std::vector<FunctionCallerID> actionsByMe();
  virtual std::vector<FunctionCallerID> actionsByMyself();
  virtual std::vector<FunctionCallerID> actionsOnMe();
  void setupType();

  std::string getName()
    {
      return mName;
    }
  int getType()
    {
      return mType;
    }
  void setName(std::string name)
  {
    mName = name;
  }
  void setType(int type)
  {
    mType = type;
  }
  
 private:
  int mType;
  std::string mName;
  
};

#endif
