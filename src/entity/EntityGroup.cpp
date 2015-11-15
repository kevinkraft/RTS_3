#include "EntityGroup.h"
#include "SpriteGroup.h"
//#include "SDL2/SDL.h"
//#include "SDL2_image/SDL_image.h"

EntityGroup::EntityGroup(SDL_Renderer *renderer, SDL_Window *window)
{  
  setWindow(window);
  setRenderer(renderer);
  
  mSpriteGroup = new SpriteGroup(renderer);
}

EntityGroup::~EntityGroup()
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      delete (*it);
    }
}

void EntityGroup::addEntity(Entity* entity)
{

  std::cout << "INFO: Adding an Entity to EntityGroup" << std::endl;
  entities.push_back(entity);
  std::cout << "INFO: Added to group vector. Getting Sprite" << std::endl;
  Sprite * sprite = entity->getSprite();
  std::cout << "INFO: Got sprite" << std::endl;
  mSpriteGroup->addSprite(sprite);
  std::cout << "INFO: returning from addEntity in EntityGroup" << std::endl;
}

Entity * EntityGroup::collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
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
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->doAction();
    }
}

void EntityGroup::removeEntity(Entity* entity)
{
  entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
  mSpriteGroup->removeSprite(entity->getSprite());
}

void EntityGroup::render(int cameraoffset_x, int cameraoffset_y, float zoom)
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->render(cameraoffset_x, cameraoffset_y, zoom);
    }    
}

void EntityGroup::setImage(std::string filename)
{
  std::cout << "INFO: In EntityGroup::setImage" << std::endl;
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->setImage(filename);
    }  
  std::cout << "INFO: Leaving EntityGroup::setImage" << std::endl;
}

//this wont work
/*void EntityGroup::setImage()
{
  //this function is necessary as some entities decide the filename internally. See Resource.
  std::cout << "INFO: In EntityGroup::setImage no argument" << std::endl;
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->setImage();
    }  
  std::cout << "INFO: Leaving EntityGroup::setImage no argument" << std::endl;
  }*/

void EntityGroup::setRenderer(SDL_Renderer *renderer)
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->getSprite()->mRenderer = renderer;
    }  
}

void EntityGroup::setWindow(SDL_Window *window)
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->getSprite()->mWindow = window;
    }  
}

void EntityGroup::update()
{
  for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
      //remove the entity if it returns false
      if ( (*it)->update() == false)
	{
	  removeEntity((*it));
	  break;
	}
    }
}
