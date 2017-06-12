//A class to hold a list of Towns in this region, a list of Resources and the map
//
//Kevin Maguire
//08/04/2017
//
//Notes
// * This class makes the Map and the Resource list for each Region

//-------------------------------------------------------------------------------------

#ifndef REGION_H_
#define REGION_H_
#include "EntityContainer.h"
#include "Map.h"
#include "Town.h"

//-------------------------------------------------------------------------------------

class Region: public EntityContainer
{
 public:

  Region(std::string name, int xpos, int ypos, int width, int height, int seed, SDL_Renderer *renderer, SDL_Window *window);
  virtual ~Region();
  void addTown(Town * tw);
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);

  Map * getMap()
  {
    return mMap;
  }

 private:

  int mPosX;
  int mPosY;
  int mWidth;
  int mHeight;

  Map * mMap;

};

#endif
