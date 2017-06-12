#include <random>
#include <ctime>

#include "Resource.h"
#include "InfoAction.h"
#include "Collect.h"
#include "global.h"
#include "TextLine.h"

Resource::Resource(float pos_x, float pos_y, int type, float amount) :
  Entity(pos_x, pos_y)
{
  setSprite( new Sprite(pos_x, pos_y, RES_CLICK_WIDTH, RES_CLICK_HEIGHT, RES_CLICK_OFFSET_X, RES_CLICK_OFFSET_Y) );
  //  setPosX(pos_x);
  //setPosY(pos_y);
  setDead(false);

  setType(type);
  setAmount(amount);
  setupType();
}

Resource::~Resource()
{}

std::vector<FunctionCallerID> Resource::actionsOnMe()
{
  std::vector<FunctionCallerID> list = Entity::actionsOnMe();
  FunctionCaller ia = &makeInfoAction;
  FunctionCallerID functionID(ia, " Info ");
  list.push_back(functionID);
  FunctionCaller coll = &makeCollect;
  FunctionCallerID functionID_coll(coll, "Collect");
  list.push_back(functionID_coll);
  return list;
}

std::string Resource::blurb()
{
  return "Resource: "+getName()+" #newline A resource contains all the raw materials that are needed.";
}

std::vector<std::string> Resource::printStats()
//make a vector of strings of the stats and pass it back
{
  std::vector<std::string> rstr{"Stat:","#vspace10","Value:","#newline"};
  std::vector<std::string> istr = {"Name:","#vspace12",getName()};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Amount:","#vspace12",makeString( getAmount() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Type:","#vspace10",makeString( getType() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"X:","#vspace13",makeString( getPosX() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  istr = {"Y:","#vspace13",makeString( getPosY() )};
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  return rstr;
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
      setAmount(DEFAULT_FOOD_RESOURCE_AMOUNT);
      break;
    case 2 :
      filename = "res/images/resources/2.png";
      setName("Wood");
      setAmount(DEFAULT_WOOD_RESOURCE_AMOUNT);
      break;
    default :
      std::cout << "Resource::setImage: ERROR: Resource Type Not Recognised" << std::endl;
    }
  Entity::setImage(filename);
}

bool Resource::update()
{
  if ( mAmount < 0.01 )
    {
      setDead(true);
      return false;
    }
  return true;
}

//-------------------------------------------------------------------------------------
// Other Functions
//-------------------------------------------------------------------------------------

void placeUniformResources(EntityGroup * Resources, int type, int number, int xlow, int ylow, int xhigh, int yhigh, int seed)
{
  //randomly places number of resource type and adds them to the entity group
  std::default_random_engine gen(seed);
  std::uniform_real_distribution<float> xfrand(xlow+0.0, xhigh+0.0);
  std::uniform_real_distribution<float> yfrand(ylow+0.0, yhigh+0.0);
  //usage frand(gen)

  for (int i = 0; i < number; i++)
    {
      Resource * res = new Resource(xfrand(gen), yfrand(gen), type);
      Resources->addEntity(res);
    }
}

void placeGroupedResources(EntityGroup * Resources, int type, int group_number, int maxgroup, float group_delta, int xlow, int ylow, int xhigh, int yhigh, int seed)
{
  //randomly places number of resource type and adds them to the entity group
  //does a second speed over the entities and adds more near previously placed entities
  std::default_random_engine gen(seed);
  std::uniform_real_distribution<float> xfrand(xlow+0.0, xhigh+0.0);
  std::uniform_real_distribution<float> yfrand(ylow+0.0, yhigh+0.0);
  std::uniform_int_distribution<int> rint(0, maxgroup);
  float delta = group_delta;
  //usage frand(gen)
  std::vector<Resource*> res_list;
  std::vector<Resource*> res_list_group;
  for (int i = 0; i < group_number; i++)
    {
      Resource * res = new Resource(xfrand(gen), yfrand(gen), type);
      res_list.push_back(res);
    }
  for (auto &itr: res_list)
    {
      int randint = rint(gen);
      float xitr = itr->getPosX();
      float yitr = itr->getPosY();
      Resources->addEntity(itr);
      int genint = rint(gen);
      for (int i=0; i < genint; i++)
        {
          std::uniform_real_distribution<float> xdelta(xitr-delta, xitr+delta);
          std::uniform_real_distribution<float> ydelta(yitr-delta, yitr+delta);
          Resource * res = new Resource(xdelta(gen), ydelta(gen), type);
          res_list_group.push_back(res);
        }
    }
  //add the resources in res list group to the EntityGroup
  for (auto &itr: res_list_group)
    Resources->addEntity(itr);
  return;
}
