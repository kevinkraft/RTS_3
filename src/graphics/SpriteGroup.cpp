#include "SpriteGroup.h"
#include "Sprite.h"
#include "SDL.h"
#include "SDL_image.h"

SpriteGroup::SpriteGroup(SDL_Renderer *renderer, bool zOrder){
  mRenderer = renderer;
  useZOrdering = zOrder;
}

SpriteGroup::~SpriteGroup(){
  for(std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it){
    delete (*it);
  }
}

void SpriteGroup::render(int cameraoffset_x, int cameraoffset_y, float zoom){
  if (useZOrdering){
    sortByZOrder();
  }

  for(std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it){
    (*it)->render(cameraoffset_x, cameraoffset_y, zoom);
  }
}

void SpriteGroup::addSprite(Sprite * sprite){
  std::cout << "INFO: In SpriteGroup::addSprite" << std::endl;
  std::cout << "INFO: Sprite pos X " << sprite->getPosX() << std::endl;
  std::cout << "INFO: Sprite pos Y " << sprite->getPosY() << std::endl;
  std::cout << "INFO: Sprite mFilename is " << sprite->getFilename() << std::endl;
  std::cout << "INFO: Size of SpriteGroup container is " << sprites.size() << std::endl;
  if (sprite->mRenderer == nullptr)
    {
      sprite->mRenderer = this->mRenderer;
      if ( this->mRenderer == nullptr )
	{
	  std::cout << "SpriteGroup:addSprite: WARN: The SpriteGroups renderer is NULL" << std::endl;
	}
    }
  sprites.push_back(sprite);
  std::cout << "INFO: Returning from  SpriteGroup::addSprite" << std::endl;
}

void SpriteGroup::removeSprite(Sprite* sprite){
  sprites.erase(std::remove(sprites.begin(), sprites.end(), sprite), sprites.end());
}

void SpriteGroup::sortByZOrder(){
  sort(sprites.begin(), sprites.end(), compareZOrder);
}

bool compareZOrder(Sprite *s1, Sprite *s2){
  return (s1->getZOrder() < s2->getZOrder());
}
