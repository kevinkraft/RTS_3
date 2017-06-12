//class for constructing Buildings

#include "Construction.h"
//#include "FunctionCaller.h"
//#include "global.h"
#include "TextLine.h"
#include "Building.h"
#include "Town.h"
#include "Construct.h"

Construction::Construction(float pos_x, float pos_y, int type) :
  EntityAction(pos_x, pos_y, 1000., CONSTRUCTION_DEFAULT_HP)
{
  setSprite( new Sprite(pos_x, pos_y, BUILDING_CLICK_WIDTH, BUILDING_CLICK_HEIGHT, BUILDING_CLICK_OFFSET_X, BUILDING_CLICK_OFFSET_Y) );
  setPosX(pos_x);
  setPosY(pos_y);

  setType(type);

  setDead(false);
  setupType();
}

Construction::~Construction()
{}

std::vector<FunctionCallerID> Construction::actionsOnMe()
{
  std::vector<FunctionCallerID> list = EntityAction::actionsOnMe();
  FunctionCaller construct = &makeConstruct;
  FunctionCallerID functionID(construct, "Construct");
  list.push_back(functionID);
  return list;
}

std::string Construction::blurb()
{
  return "Construction: "+getName()+" #newline A Construction is the site at which a building will be made.";
}

bool Construction::needsMaterials()
{
  //returns true if no more materials are needed
  bool needs_materials = false;
  for ( auto &itm: mMaterialsMap)
    {
      if ( itm.second > 0.01)
        needs_materials = true;
    }
  return needs_materials;
}

std::pair<int, float> Construction::nextItemNeeded()
{
  //returns a pair of item type int and amount needed
  std::pair<int,float> ret_pair;
  for ( auto &itm: mMaterialsMap)
   {
    if ( itm.second > 0.01)
      {
        ret_pair.first = itm.first;
        ret_pair.second = itm.second;
        break;
      }
   }
  return ret_pair;
}

std::vector<std::string> Construction::printStats()
{
  // I NEED TO MAKE A GLOBAL MAP OF ITEM TYPE INT AND ITEM NAME

  std::vector<std::string> rstr = this->EntityAction::printStats();
  std::vector<std::string> istr = {"WorkLeft:","#vspace4", makeString(mWork) };
  rstr.insert( rstr.end(), istr.begin(), istr.end() );
  rstr.push_back("#newline");
  std::string nstr = "";
  for (auto &itm: mMaterialsMap)
    {
      switch ( itm.first )
        {
          case 1: //food
            nstr = "food";
            break;
          case 2: //wood
            nstr = "wood";
            break;
          default:
            std::cout << "Construction::printStats: ERROR: Item type for materials needed not recognised" << std::endl;
        }
      istr = {nstr+":","#vspace5",makeString( itm.second )};
      rstr.insert( rstr.end(), istr.begin(), istr.end() );
      rstr.push_back("#newline");
    }
  return rstr;
}

void Construction::setupType()
{
  //Caution: you need to set the sprite renderer before you do this
  std::string filename = "res/images/constructions/0.png";
  switch (mType)
    {
    case 0: //main hut
      setName("Hut Construction");
      mMaterialsMap = HUT_CONSTRUCTION_MATERIALS;
      mWork = 100.;
      break;
    case 1: //stockpile
      setName("Stockpile Construction");
      mMaterialsMap = STOCKPILE_CONSTRUCTION_MATERIALS;
      mWork = 100.;
      break;
    default:
      std::cout << "Construction::setType: ERROR: Construction Type Not Recognised" << std::endl;
    }
  Entity::setImage(filename);
}

bool Construction::update()
{
  //remove items from the inventory, and subtract the amounts from the materials map
  for ( auto &itm: getInventory()->mItems )
    {
      if ( !mMaterialsMap.count(itm->getType()) )
        {
          TerminalText::printTerminal("WARN: Construction::Update: This item is not needed for this Construction.");
          getInventory()->removeItem(itm);
          continue;
        }
      float amount = itm->getAmount();
      if ( mMaterialsMap[itm->getType()] < itm->getAmount() )
        amount = mMaterialsMap[itm->getType()];
      mMaterialsMap[itm->getType()] = mMaterialsMap[itm->getType()] - amount;
      getInventory()->removeItem(itm);
      if ( mMaterialsMap[itm->getType()] < 0.01 )
        mMaterialsMap[itm->getType()] = 0.;
    }
  //check if it has all the materials
  if ( needsMaterials() == false )
    {
      //make the building if all the work is done
      if ( mWork <= 0. )
        {
          Building * bld = new Building( getPosX(), getPosY(), mType);
          this->getTown()->addEntity( bld );
          return false; //will be removed
        }

    }




  return EntityAction::update();
}

