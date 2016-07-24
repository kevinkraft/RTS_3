//building class
//

#include "Building.h"
#include "FunctionCaller.h"
#include "global.h"

Building::Building(float pos_x, float pos_y, int type) :
  EntityAction(pos_x, pos_y, 0.)
{
  setSprite( new Sprite(pos_x, pos_y, BUILDING_CLICK_WIDTH, BUILDING_CLICK_HEIGHT, BUILDING_CLICK_OFFSET_X, BUILDING_CLICK_OFFSET_Y) );
  setPosX(pos_x);
  setPosY(pos_y);
  
  setType(type);

  setDead(false);
}

Building::~Building()
{}

std::vector<FunctionCallerID> Building::actionsByMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsByMe();
  return list;
}

std::vector<FunctionCallerID> Building::actionsByMyself()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsByMyself();
  return list;
}

std::vector<FunctionCallerID> Building::actionsOnMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsOnMe();
  return list;
}

void Building::setupType()
{
  //Caution: you need to set the sprite renderer before you do this
  std::string filename;
  switch (mType)
    {
    case 0: //main hut
      setName("Hut");
      filename = "res/images/buildings/0_2.png";
      break;
    default:
      std::cout << "Building::setType: ERROR: Building Type Not Recognised" << std::endl;
    }
  Entity::setImage(filename);
}

