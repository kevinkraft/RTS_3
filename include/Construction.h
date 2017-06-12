#ifndef CONSTRUCTION_H_
#define CONSTRUCTION_H_

//#include <string>
//#include <iostream>
#include <map>

//#include "FunctionCaller.h"
#include "EntityAction.h"

class Construction: public EntityAction
{
 public:

  Construction(float pos_x, float pos_y, int building_type);
  virtual ~Construction();

  virtual std::vector<FunctionCallerID> actionsOnMe();
  std::string blurb();
  bool needsMaterials();
  std::pair<int,float> nextItemNeeded();
  std::vector<std::string> printStats();
  void setupType();
  bool update();

  int getType()
    {
      return mType;
    }
  float getWork()
    {
      return mWork;
    }
  void setType(int type)
  {
    mType = type;
  }
  void setWork(float w)
  {
    mWork = w;
  }

 private:

  int mType; //same as Building type
  std::map<int, float> mMaterialsMap; //type, amount
  float mWork;

};

#endif

