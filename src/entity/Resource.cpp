#include <random>
#include <ctime>

#include "Resource.h"
#include "InfoAction.h"
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
  FunctionCaller ia = &makeInfoAction;
  FunctionCallerID functionID(ia, " Info ");
  list.push_back(functionID);
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
      break;
    default :
      std::cout << "Resource::setImage: ERROR: Resource Type Not Renognised" << std::endl;
    }
  Entity::setImage(filename);
}

//-------------------------------------------------------------------------------------
// Other Functions
//-------------------------------------------------------------------------------------

void placeResources(EntityGroup * Resources, int type, int number)
{
  //randomly places number of resource type and adds them to the entity group
  std::default_random_engine gen(time(NULL));
  std::uniform_real_distribution<float> frand(0., MAP_SIZE+0.0);
  //usage frand(gen)

  for (int i = 0; i < number; i++)
    {
      Resource * res = new Resource(frand(gen), frand(gen), type, DEFAULT_RESOURCE_AMOUNT);
      Resources->addEntity(res);
    }
}
