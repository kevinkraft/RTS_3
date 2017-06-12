#include "EntityGroup.h"
#include "SpriteGroup.h"
//#include "SDL2/SDL.h"
//#include "SDL2_image/SDL_image.h"
#include "Map.h"

EntityGroup::EntityGroup(SDL_Renderer *renderer, SDL_Window *window)
{
  setWindow(window);
  setRenderer(renderer);

  mSpriteGroup = new SpriteGroup(renderer);
}

EntityGroup::~EntityGroup()
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      delete (*it);
    }
}

void EntityGroup::addEntity(Entity* entity)
{
  std::cout << "INFO: Adding an Entity to EntityGroup" << std::endl;
  mEntities.push_back( entity );
  std::cout << "INFO: Added to group vector. Getting Sprite" << std::endl;
  Sprite * sprite = entity->getSprite();
  std::cout << "INFO: Got sprite" << std::endl;
  mSpriteGroup->addSprite(sprite);
  std::cout << "INFO: returning from addEntity in EntityGroup" << std::endl;
  entity->setupType();
}

Entity * EntityGroup::collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      if ( (*it)->collide(x, y, cameraoffset_x, cameraoffset_y, zoom) == true)
        {
          return (*it);
        }
    }
  return nullptr;
}

void EntityGroup::doActions()
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->doAction();
    }
}

Entity * EntityGroup::getClosest(float x, float y)
{
  //return the entity in the list closest to x,y
  Entity * ret_ent;
  float dist = 0.;
  float smallest_dist = -1.;
  for (auto &ent: mEntities)
    {
      dist = fabs( getDistBetween(ent->getPosX(), ent->getPosY(), x, y) );
      if ( dist < smallest_dist || smallest_dist == -1.)
        {
          smallest_dist = dist;
          ret_ent = ent;
        }
    }
  return ret_ent;
}

Entity * EntityGroup::getEntity(std::string ename)
{
  Entity * ret_ent = nullptr;
  for (auto &ent: mEntities)
  {
    if ( ent->getName() == ename )
      {
        //make sure the entity name is unique in the group
        if ( ret_ent != nullptr )
          {
            std::cout << "WARN: EntityGroup::getEntity: Name " << ename << " matches more than one entity in the group. Returning nullptr." << std::endl;
            return nullptr;
          }
        else
          ret_ent = ent;
      }
  }
  return ret_ent;
}

void EntityGroup::removeEntity(Entity* entity)
{
  mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), entity), mEntities.end());
  mSpriteGroup->removeSprite(entity->getSprite());
  delete entity;
}

void EntityGroup::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->render(cameraoffset_x, cameraoffset_y, zoom);
    }
}

void EntityGroup::setImage(std::string filename)
{
  std::cout << "INFO: In EntityGroup::setImage" << std::endl;
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->setImage(filename);
    }
  std::cout << "INFO: Leaving EntityGroup::setImage" << std::endl;
}

//this wont work
/*void EntityGroup::setImage()
{
  //this function is necessary as some mEntities decide the filename internally. See Resource.
  std::cout << "INFO: In EntityGroup::setImage no argument" << std::endl;
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->setImage();
    }
  std::cout << "INFO: Leaving EntityGroup::setImage no argument" << std::endl;
  }*/

void EntityGroup::setRenderer(SDL_Renderer *renderer)
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->getSprite()->mRenderer = renderer;
    }
}

void EntityGroup::setWindow(SDL_Window *window)
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      (*it)->getSprite()->mWindow = window;
    }
}

void EntityGroup::update()
{
  for(std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
    {
      //remove the entity if it returns false
      if ( (*it)->update() == false)
        {
          removeEntity((*it));
          break;
        }
    }
}
