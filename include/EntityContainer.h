//Base class for lists of EntityGroups for running the usual loop functions easily
//
//Kevin Maguire
//08/04/2017
//
//Notes
// * This class contains a map of EntityGroups
// * It also contains a map of lists of EntityContainers
//   * In this way it can contain sub lists of its own class type
// * It runs update, render, collide and doAction functions on its contained
//   classes, which allow these function to be run easily on a large number of entities
//   all at once

//-------------------------------------------------------------------------------------

#ifndef ENTITYCONTAINER_H_
#define ENTITYCONTAINER_H_

#include <map>

#include "SDL.h"

#include "Selectable.h"
#include "EntityGroup.h"

//-------------------------------------------------------------------------------------

class EntityContainer: public Selectable
{
 public:
  EntityContainer(std::string name, SDL_Renderer *renderer, SDL_Window *window);
  virtual ~EntityContainer();

  void addContainer( std::string id, EntityContainer * ec );
  void addContainers( std::string id, std::vector<EntityContainer*> ecs );
  void addEntity(std::string id, Entity * ent);
  void addEntityGroup(std::string id, EntityGroup * eg);
  Entity * collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom);
  void doActions();
  std::vector<EntityContainer*> * getContainerGroup(std::string gname);
  Entity * getEntity(std::string ename);
  EntityGroup * getEntityGroup(std::string gname);
  virtual void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0, std::vector<std::string> * group_order = nullptr);
  virtual void update();

  int getNContainers()
  {
    return mContainerMap.size();
  }

  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;

  protected:
    std::map<std::string,EntityGroup*> mGroupMap;
    std::map< std::string, std::vector<EntityContainer*> > mContainerMap;

};

#endif
