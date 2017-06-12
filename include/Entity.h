#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <iostream>
#include <vector>
#include <cstdarg>

//#include "SDL2/SDL.h"
//#include "SDL2_image/SDL_image.h"

#include "Sprite.h"
#include "Action.h"
#include "Selectable.h"
//#include "global.h"
//#include "texture.h"

class Entity: public Selectable
{
 public:

  Entity(float pos_X, float pos_y, bool dead = false);
  //Entity();
  virtual ~Entity();

  virtual std::vector<FunctionCallerID> actionsOnMe();
  virtual std::string blurb();
  bool collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom);
  void render(int cameraoffset_x, int cameraoffset_y, float zoom, int height = 0);
  virtual void setImage(std::string image);
  virtual void setupType();
  virtual bool update();

  virtual void doAction()
  {
    //std::cout << "WARN: Entity::doAction: This entity can't do actions." << std::endl;
  }
  std::string getName()
  {
    return mName;
  }
  float getPosX() const
  {
    return mPos_x;
  }
  float getPosY() const
  {
    return mPos_y;
  }
  Sprite * getSprite()
  {
    return mSprite;
  }
  bool isDead()
  {
    return mDead;
  }
  void setDead(bool dead)
  {
    mDead = dead;
  }
  void setName(std::string name)
  {
    mName = name;
  }
  void setPosX(float posx)
  {
    mPos_x = posx;
    mSprite->setPosX(posx);
  }
  void setPosY(float posy)
  {
    mPos_y = posy;
    mSprite->setPosY(posy);
  }
  void setSprite(Sprite * sprite)
  {
    mSprite = sprite;
  }

 protected:
  //  std::string mName = "NAME";

 private:
  float mPos_x;
  float mPos_y;

  bool mDead;
  Sprite * mSprite;

};

#endif
