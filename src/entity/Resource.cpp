#include <random>

#include "Resource.h"
#include "global.h"

Resource::Resource(float pos_x, float pos_y, int type, float amount) :
  Entity()
{
  setSprite( new Sprite(pos_x, pos_y, RES_CLICK_WIDTH, RES_CLICK_HEIGHT, RES_CLICK_OFFSET_X, RES_CLICK_OFFSET_Y) );
  setPosX(pos_x);
  setPosY(pos_y);
  setDead(false);

  setType(type);
  setAmount(amount);
}

Resource::~Resource()
{}

std::vector<FunctionCallerID> Resource::actionsOnMe()
{
  //NEED TO ADD THE COLLECT ACTION IN HERE
  /*std::vector<FunctionCallerID> list;
  FunctionCaller coll = &makeAttack; 
  FunctionCallerID functionID(att, "Attack");
  list.push_back(functionID);
  return list;*/
  std::vector<FunctionCallerID> list = Entity::actionsOnMe();
  return list;
}

void Resource::setupType()
{
  //set an image for the resource based on the type
  std::string filename;
  std::cout << "Resourec::setImage: INFO: Type is: " << mType << std::endl;
  switch ( mType )
    {
    case 1 :
      filename = "res/images/resources/1.png";
      setName("Food");
      break;
    default :
      std::cout << "Resource::setImage: ERROR: Resource Type Not Renognised" << std::endl;
    }
  Entity::setImage(filename);
}

//-------------------------------------------------------------------------------------
// Other Functions
//-------------------------------------------------------------------------------------

void placeResources(EntityGroup * Resources, int type, int amount)
{
  //randomly places amount of resource type and adds them to the entity group
  
  std::default_random_engine gen(time(NULL));
  std::uniform_real_distribution<float> frand(0., MAP_SIZE+0.0);  
  //usage frand(gen)
  
  for (int i = 0; i < amount; i++)
    {
      Resource * res = new Resource(frand(gen), frand(gen), type, DEFAULT_RESOURCE_AMOUNT);
      Resources->addEntity(res);
    }
}
