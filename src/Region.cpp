//#include <iostream>
//#include "Town.h"
//#include "Unit.h"
//#include "Building.h"
//#include "TextLine.h"
#include "Region.h"
#include "TextLine.h"
#include "Resource.h"

Region::Region(std::string name, int xpos, int ypos, int width, int height, int seed, SDL_Renderer *renderer, SDL_Window *window)
  : EntityContainer(name, renderer, window)
{
  mPosX = xpos;
  mPosY = ypos;
  mWidth = width;
  mHeight = height;

  EntityGroup * res = new EntityGroup(renderer, window);
  //placeUniformResources(res, 1, MAP_SIZE/2, xpos, ypos, xpos+width, ypos+height, seed);
  placeGroupedResources(res, 1, MAP_SIZE/2, 3, 1, xpos, ypos, xpos+width, ypos+height, seed+1);
  placeGroupedResources(res, 2, MAP_SIZE/4, 70, 3, xpos, ypos, xpos+width, ypos+height, seed+1);
  mGroupMap["resources"] = res;

  //make the map
  mMap = new Map(xpos, ypos, width, height, seed, renderer, window);
}

Region::~Region()
{
  TerminalText::printTerminal("INFO: Region::~Region: Deleting Region.");
}

void Region::addTown(Town * tw)
{
  tw->setRegion(this);
  addContainer("towns", tw);
}

void Region::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  //dont render the map here, need to do it separately so that units from different regions are not cover by this map
  //getMap()->render(cameraoffset_x, cameraoffset_y, zoom);
  //render everything else
  std::vector<std::string> * group_order = new std::vector<std::string>({"resources","constructions","buildings","units"});
  EntityContainer::render(cameraoffset_x, cameraoffset_y, zoom, group_order);
}



