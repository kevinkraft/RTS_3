#include <iostream>
#include "Town.h"
#include "Unit.h"
#include "Building.h"
#include "Construction.h"
#include "TextLine.h"

Town::Town(std::string name, SDL_Renderer *renderer, SDL_Window *window)
  : EntityContainer(name, renderer, window)
{
  mGroupMap["buildings"] = new EntityGroup(renderer, window);
  mGroupMap["units"] = new EntityGroup(renderer, window);
  mGroupMap["constructions"] = new EntityGroup(renderer, window);
  mRegion = nullptr;
}

Town::~Town()
{
  TerminalText::printTerminal("INFO: Town::~Town: Deleting Town.");
}

void Town::addEntity(Entity * ent)
{
  if ( dynamic_cast<Unit*>(ent) )
    {
      dynamic_cast<Unit*>(ent)->setTown(this);
      mGroupMap["units"]->addEntity( ent );
    }
  else if ( dynamic_cast<Building*>(ent) )
    {
      dynamic_cast<Building*>(ent)->setTown(this);
      mGroupMap["buildings"]->addEntity( ent );
    }
  else if ( dynamic_cast<Construction*>(ent) )
    {
      dynamic_cast<Construction*>(ent)->setTown(this);
      mGroupMap["constructions"]->addEntity( ent );
    }
  else
    TerminalText::printTerminal("WARN: Town::addEntity: Only a Unit, Building or Constreuction can be added to the Town.");
}

void Town::setUnitImage( std::string filename )
{
  mGroupMap["units"]->setImage( filename );
}

void Town::setStockpile(Building * bld)
{
  Entity * ent = getEntity( bld->getName() );
  if ( ent == nullptr )
    {
      //the stockpile is not yet in the lists of entities
      EntityContainer::addEntity( "buildings", bld );
    }
  mStockpile = bld;
}

void Town::update()
{
  //set the stockpile to a building of type=stockpile, if not already the case
  if ( mStockpile->getType() != 1)
    {
      for (auto &itb: mGroupMap["buildings"]->mEntities)
        {
          if ( dynamic_cast<Building*>(itb)->getType() == 1 )
            setStockpile(dynamic_cast<Building*>(itb));
        }
    }
  EntityContainer::update();
}

