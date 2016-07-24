#include "Sprite.h"
#include "Entity.h"
#include "global.h"
//#include "texture.h"
//#include "SDL2/SDL.h"
//#include "SDL2_image/SDL_image.h"

Entity::Entity(float pos_x, float pos_y, bool dead)
{  

  mSprite = new Sprite(pos_x, pos_y);
  setPosX(pos_x);
  setPosY(pos_y);

  setDead(dead);

}

//Entity::Entity()
//{}

Entity::~Entity()
{
  //std::cout << "Deleting Entity" << std::endl;
}

std::vector<FunctionCallerID> Entity::actionsOnMe()
{
  std::cout << "Entity::actionsOnMe: WARN: This function should not be called" << std::endl;
  std::vector<FunctionCallerID> list;
  return list;
}

bool Entity::collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  return mSprite->collide(x, y, cameraoffset_x, cameraoffset_y, zoom);
}

void Entity::setImage(std::string image)
{
  std::cout << "INFO: In Entity::setImage" << std::endl;
  mSprite->setFilename(image);
  std::cout << "INFO: After setting the filename of the sprite entitye" << std::endl;
  mSprite->loadImage();
  std::cout << "INFO: Leaving Entity::setImage" << std::endl;
}

void Entity::setupType()
{
  //this is just a virtual function to be overwritten by some entites
  std::cout << "Entity::setType: INFO: In This Function" << std::endl;
}

void Entity::render(int cameraoffset_x, int cameraoffset_y, float zoom, int height)
{
  mSprite->render(cameraoffset_x, cameraoffset_y, zoom, height);
}

bool Entity::update()
{
  if (isDead())
    {
      return false;
    }
  return true;
}

