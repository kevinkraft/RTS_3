//Entity info menu
//
//Kevin Maguire
//24/07/2016
//

//Note:
// * Menu for displaying info about entities
//   * work on EntityAction and Resource
//   * display different info depending on what class you give it

//Add:
// * populate function
//   * one for EntityAction and one for Resourse

//-------------------------------------------------------------------------------------

#ifndef INFOMENU_H_
#define INFOMENU_H_

//#include <string>
//#include <iostream>

//#include "Button.h"
//#include "Map.h"
#include "EntityAction.h"
#include "Menu.h"
#include "Resource.h"
#include "TextMaker.h"

//-------------------------------------------------------------------------------------

class InfoMenu: public Menu
{
 public:
  
  InfoMenu(float x, float y, float width, float height, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  InfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker);
  virtual ~InfoMenu();

  void populate(EntityAction * ea);
  void populate(Resource * r);
  void setup();

  Entity * getEntity()
  {
    if ( mEntityAction )
      return dynamic_cast<Entity*>(mEntityAction);
    else if ( mResource )
      return dynamic_cast<Entity*>(mResource);
    else
      return nullptr;
  }
  EntityAction * getEntityAction()
  {
    return mEntityAction;
  }
  Resource * getResource()
  {
    return mResource;
  }
  void setEntityAction( EntityAction * ea)
  {
    mEntityAction = ea;
  }
  void setResource( Resource * r)
  {
    mResource = r;
  }

 private:

  EntityAction * mEntityAction = nullptr;
  Resource * mResource = nullptr;
  
};

#endif
