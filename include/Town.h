//Class for a Town which contains building and entities
//
//Kevin Maguire
//02/04/2017
//

//-------------------------------------------------------------------------------------

#ifndef TOWN_H_
#define TOWN_H_
#include "EntityContainer.h"
#include "EntityGroup.h"
#include "Building.h"

class Region;

//-------------------------------------------------------------------------------------

class Town: public EntityContainer
{
 public:

  Town(std::string name, SDL_Renderer *renderer, SDL_Window *window);
  virtual ~Town();

  void addEntity(Entity * entity);
  void setUnitImage(std::string filename);
  void setStockpile(Building * bld);
  void update();

  EntityGroup * getBuildings()
  {
    return mGroupMap["buildings"];
  }
  EntityGroup * getConstructions()
  {
    return mGroupMap["constructions"];
  }
  Region * getRegion()
  {
    return mRegion;
  }
  Building * getStockpile()
  {
    return mStockpile;
  }
  EntityGroup * getUnits()
  {
    return mGroupMap["units"];
  }
  void setRegion(Region * rg)
  {
    mRegion = rg;
  }

 private:
    Building * mStockpile;
    Region * mRegion;

};

#endif
