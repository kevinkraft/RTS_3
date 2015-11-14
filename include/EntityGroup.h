#ifndef ENTITYGROUP_H_
#define ENTITYGROUP_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


//#include "global.h"
#include "Entity.h"
#include "SpriteGroup.h"


class EntityGroup
{
 public:
  EntityGroup(SDL_Renderer *renderer, SDL_Window *window);
  virtual ~EntityGroup();

  void addEntity(Entity * entity);
  Entity * collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom);
  void doActions();
  void removeEntity(Entity * entity);  
  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
  void setImage(std::string filename);
  void setRenderer(SDL_Renderer *renderer);
  void setWindow(SDL_Window *window);
  void update();
    
  std::vector<Entity*> entities;
  SpriteGroup * mSpriteGroup;
    
};

#endif /* ENTITYGROUP_H_ */
