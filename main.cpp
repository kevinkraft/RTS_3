//Main implementation and game loop
//
//Kevin Maguire
//18/08/15
//
//Version 0.7
//

//Add:
// * stockpile
//   * so beginnings of building class
//     * add a unit inventory to building
//     * be careful, the default range and att damage of an EntityAction is set to the unit values, need to fix
// * collect resource action
// * Low Priority:
//   * InfoMenu
//     * it would be nice if the InfoMenu updated in real time

//Problem:
// * Exchange Menu
//   * when you open a second menu you cant immediately select the item that was previously clicked when the menu was
//     previously opened. I implemented something to stop you clicking twice on a button, this must not be cancelled
//     when the menu is repopulated for another exchange action.
// * After playing for awhile the PopMenu buttons disappeared?
//   * Gives error: "LoadBMP error: Out of memory"
//     * I probably am not deleting the button sprite correctly
//   * The menus are also blank
//     * Gives errors:
//       * CreateTexture error: SDL_CreateTextureFromSurface() passed NULL surface
//       * TTF_LoadTextLine error: Out of memory
//   * unit selection menu still works, probably because it is never recreate, buttons are always the same
//   * I was able to replicate by opening and closing loads of menus
//     * I opened and closed lots of exchange menus before the problem appeared. I also did it with the pop menu but not sure it
//       filled up as much memory as the exchange menu does.
//     * The PopMenu alone is enough to cause this problem after about 3 minutes of constant opening and closing
// * If you right click, the pop menu comes up, if you then left click off the menu and right click again the buttons are duplicated
//   * It essentially allows you to have commands related to two different coords/entities in the same pop menu
// * The setPositions function of the DisplayPiece class doesnt work?
//   * I needed to set the relative positions in the constructors or relative DisplayPieces
//     * I don't understand why this is necessary as setPositions is supposed to do that for me at the
//       end of the constructor
//   * I bet if I change the pos of the DisplayPiece during the game it wouldn't actually move
// * Does the width and height given to make a TextLine actually do anything?
//   * clearly not if the texture that it makes has different dimensions
//   * changing the text height definitely has an affect
//   * for TextBox scrolling this matters, use the height from the texture instead
// * The height of a text line returned from the texture is much larger than it should be
//   * this results in the text box scroll function being created when the text is not larger than the
//     text box.
//   * I will have to tune the line height so that it works, but this will change if the font size change

//-------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include <SDL.h>

#include "global.h"
#include "logging.h"
#include "Timer.h"
#include "Sprite.h"
#include "SpriteGroup.h"
#include "EntityGroup.h"
#include "EntityAction.h"
#include "Unit.h"
#include "Movement.h"
#include "Attack.h"
#include "InfoMenu.h"
#include "ExchangeMenu.h"
#include "Menu.h"
#include "PopMenu.h"
#include "SubMenu.h"
#include "SelectionMenu.h"
#include "MenuGroup.h"
#include "Map.h"
#include "Action.h"
#include "TextMaker.h"
#include "TextLine.h"
#include "Resource.h"
#include "Building.h"
#include "Exchange.h"

//-------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
  //-------------------------------------------------------------------------------------
  // Variable declarations
  //-------------------------------------------------------------------------------------
  bool quit = false;
  SDL_Event event;

  Timer fpsTimer;
  int countedFrames = 0;
  Timer capTimer;

  int cameraoffset_x = 0;
  int cameraoffset_y = 0;
  const int SCROLL_SPEED = 10;

  int mouse_x = 0;
  int mouse_y = 0;
  int screen_width = SCREEN_WIDTH;
  int screen_height = SCREEN_HEIGHT;

  bool scroll_active = true;
  bool fullscreen = false;
  bool use_custom_cursor = USE_CUSTOM_CURSOR;
  bool debug_mode = false;

  float zoom = 1.0;

  //-------------------------------------------------------------------------------------
  //Initialization:
  //-------------------------------------------------------------------------------------
  //initialise
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      logSDLError(std::cout, "SDL_Init");
      return 1;
    }
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
      logSDLError(std::cout, "IMG_Init");
      SDL_Quit();
      return 1;
    }
  if (TTF_Init() != 0)
    {
      logSDLError(std::cout, "TTF_Init");
      SDL_Quit();
      return 1;
    }

  SDL_Window *window = nullptr;
  window = SDL_CreateWindow("Civ",
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);
  if (window == nullptr)
    {
      logSDLError(std::cout, "CreateWindow");
      return 1;
    }

  SDL_Renderer *renderer = nullptr;
  if (VSYNC_ACTIVE)
    {
      renderer = SDL_CreateRenderer(window, -1,
				    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
  else
    {
      renderer = SDL_CreateRenderer(window, -1,
				    SDL_RENDERER_ACCELERATED);
    }
  if (renderer == nullptr)
    {
      logSDLError(std::cout, "CreateRenderer");
      return 1;
    }

  if (use_custom_cursor)
    {
      SDL_ShowCursor(false);
    }

  //-------------------------------------------------------------------------------------
  // Create objects:
  //-------------------------------------------------------------------------------------
  SDL_Texture *texture_cursor  = loadTexture("res/images/cursor.png", renderer, false);

  Map map(renderer, window);

  Sprite *sprite_selection = new Sprite("res/images/iso/selection.png", 2, 2, renderer, window, TILE_SIZE);

  //make an entity and move it
  std::cout << "Main: INFO: Starting To Make Objects" << std::endl;
  Unit * unit_you = new Unit(2., 2., "You");
  Unit * unit1 = new Unit(2, 3, "Unit1");
  EntityAction * selected_entity = unit_you;
  //Movement * move1 = new Movement(10., 8.);
  //unit_you->appendAction(move1);
  Movement * move2 = new Movement(0., 0.);
  //unit1->appendAction(move2);
  //Attack * attack = new Attack(unit1);
  //unit_you->appendAction(attack);

  //make a group to hold units
  EntityGroup * Units = new EntityGroup(renderer, window);
  Units->addEntity(unit_you);
  Units->addEntity(unit1);

  //make loads of units
  Unit * unit_loop;
  std::string uloop_name = "";
  for (int i = 0; i<5; i++)
  {
    std::stringstream ul_ss;
    ul_ss << "Unit" << i+2;
    uloop_name = ul_ss.str();
    unit_loop = new Unit(0.+i*0.5, 0., uloop_name);
    Units->addEntity(unit_loop);
  }

  //set the image filename of the group
  std::cout << "Main: INFO: Setting the Units image file" << std::endl;
  Units->setImage("res/images/units/villager.png");

  //make a text maker
  TextMaker * TextHandler = new TextMaker("res/fonts/KaushanScript-Regular.otf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/Pacifico.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/FFF_Tusj.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/sample.ttf", renderer, window);

  //make a temp message
  //TextLine * message = new TextLine(30. + 122., 125., 500., 50., "HELLO WORLD RTS 3", TextHandler);
  //message->setActive(true);

  //make a pop_menu
  PopMenu * pop_menu = new PopMenu(renderer, window, TextHandler);
  //pop_menu->loadImage("res/images/menu/menu.png");

  //make a menu group
  MenuGroup * Menus = new MenuGroup();
  Menus->addMenu(pop_menu);

  //make a group to hold resources
  EntityGroup * Resources = new EntityGroup(renderer, window);
  placeResources(Resources, 1, MAP_SIZE/2);

  //make a resource
  //Resource * res_food = new Resource(0., 0., 1, 100.);
  //Resources->addEntity(res_food);
  //res_food->setImage();

  //make items and give it to the unit
  Item* food1 = new Item(1., 5.);
  Item* wood1 = new Item(2., 1.);
  unit_you->addItem(food1);
  unit_you->addItem(wood1);
  unit_you->printInventory();
  Item* food2 = new Item(1., 1.);
  unit1->addItem(food2);

  //make exchange action
  Unit * unit3 = (Unit*) Units->getEntity("Unit3");
  Item* food3 = new Item(1., 1.);
  unit3->addItem(food3);
  //if ( unit3 == nullptr )
  //  std::cout << "ERRO: main: Creating Objects: unit3 is a nullptr." << std::endl;
  //Exchange * ex = new Exchange( dynamic_cast<EntityAction*>(unit3), 1, 5.1);
  //Exchange * ex = new Exchange( dynamic_cast<EntityAction*>(unit3), 1, 8);
  //unit1->clearAddAction(ex);
  Unit * unit4 = (Unit*) Units->getEntity("Unit4");
  Item* wood2 = new Item(2., 1.);
  unit4->addItem(wood2);

  //make buildings
  //make a group to hold buildings
  EntityGroup * Buildings = new EntityGroup(renderer, window);
  Building * hut = new Building(3., 3., 0);
  Buildings->addEntity(hut);

  //make menus
  InfoMenu * info_menu = new InfoMenu(renderer, window, TextHandler);
  info_menu->setActive(false);
  Menus->addMenu(info_menu);
  //ExchangeMenu * exchange_menu = new ExchangeMenu(renderer, window, TextHandler);
  ExchangeMenu * exchange_menu = new ExchangeMenu(renderer, window, TextHandler);
  exchange_menu->setActive(false);
  Menus->addMenu(exchange_menu);

  //make the unit selection menu
  Menu * unit_sel_menu = new Menu(0, 0, 500, 600, renderer, window, TextHandler);
  unit_sel_menu->makeCloseButton();
  SelectionMenu * sl = new SelectionMenu(0, 0.05*unit_sel_menu->getHeight(), 1, 0.95, unit_sel_menu, Units );
  unit_sel_menu->addSelectionMenu( sl );
  Menus->addMenu( unit_sel_menu );

  //Start timers:
  fpsTimer.start();

  //-------------------------------------------------------------------------------------
  // Main loop:
  //-------------------------------------------------------------------------------------
  while (!quit)
    {
      if (!VSYNC_ACTIVE)
        {
          capTimer.start();
        }

      //-------------------------------------------------------------------------------------
      // Update Entity states
      //-------------------------------------------------------------------------------------
      //TerminalText::printTerminal("INFO: main: Updates Section: About to update the entities.");
      Units->update();
      Resources->update();
      Buildings->update();
      if ( unit_sel_menu->isActive() == true && unit_sel_menu->getSelectionMenu(0)->hasSelection() == true)
        selected_entity = dynamic_cast<EntityAction*>(unit_sel_menu->getSelectionMenu(0)->getSelection());

      //-------------------------------------------------------------------------------------
      // Entity operations
      //-------------------------------------------------------------------------------------
      //TerminalText::printTerminal("INFO: main: Actions Section: About to do the Unit actions.");
      Units->doActions();
      Buildings->doActions();
      //TerminalText::printTerminal("INFO: main: Actions Section: Finished the Entities actions.");

      //-------------------------------------------------------------------------------------
      // Screen
      //-------------------------------------------------------------------------------------

      //Mouse position:
      SDL_GetMouseState(&mouse_x, &mouse_y);

      //Resolution:
      SDL_GetWindowSize(window, &screen_width, &screen_height);

      if (scroll_active)
        {
          if (mouse_x < 20 ) // cameraoffset_x > map.getMinPixelX(zoom))
            {
              cameraoffset_x -= SCROLL_SPEED;
            }
          if (mouse_x > screen_width-20 ) // cameraoffset_x < map.getMaxPixelX(zoom)-screen_width+TILE_SIZE*zoom)
            {
              cameraoffset_x += SCROLL_SPEED;
            }
          if (mouse_y > screen_height-20 ) // cameraoffset_y < map.getMaxPixelY(zoom)-screen_height+TILE_SIZE*zoom)
            {
              cameraoffset_y += SCROLL_SPEED;
            }
          if (mouse_y < 20 ) // cameraoffset_y > map.getMinPixelY(zoom))
            {
              cameraoffset_y -= SCROLL_SPEED;
            }
        }

      //-------------------------------------------------------------------------------------
      //Events:
      //-------------------------------------------------------------------------------------
      while (SDL_PollEvent(&event))
        {
          if (event.type == SDL_QUIT)
            {
              quit = true;
            }
          else if (event.type == SDL_KEYDOWN)
            {
          if (event.key.keysym.sym == SDLK_ESCAPE)
              {
                quit = true;
              }
          else if (event.key.keysym.sym == SDLK_RIGHT)
            {
              cameraoffset_x += SCROLL_SPEED*2;
            }
          else if (event.key.keysym.sym == SDLK_LEFT)
            {
              cameraoffset_x -= SCROLL_SPEED*2;
            }
          else if (event.key.keysym.sym == SDLK_UP)
            {
              cameraoffset_y -= SCROLL_SPEED*2;
            }
          else if (event.key.keysym.sym == SDLK_DOWN)
            {
              cameraoffset_y += SCROLL_SPEED*2;
            }
          else if (event.key.keysym.sym == SDLK_f)
            {
              fullscreen = not(fullscreen);
              if (fullscreen)
                {
                  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                }
              else
                {
                  SDL_SetWindowFullscreen(window, 0);
                }
            }
            else if (event.key.keysym.sym == SDLK_g)
              {
                map.setDrawGrid(not(map.getDrawGrid()));
              }
            else if (event.key.keysym.sym == SDLK_c)
              {
                use_custom_cursor = not(use_custom_cursor);
                SDL_ShowCursor(not(use_custom_cursor));
              }
            else if (event.key.keysym.sym == SDLK_d)
              {
                debug_mode = not(debug_mode);
              }
            else if (event.key.keysym.sym == SDLK_s)
              {
                scroll_active = not(scroll_active);
              }
            else if (event.key.keysym.sym == SDLK_u)
              {
                if ( unit_sel_menu->isActive() == false )
                  unit_sel_menu->setActive(true);
                else if ( unit_sel_menu->isActive() == true )
                  unit_sel_menu->setActive(false);
              }
            else if (event.key.keysym.sym == SDLK_t)
              {
                for ( int i=0; i < unit_you->getActions()->getSize(); i++ )
                  {
                    if ( dynamic_cast<Exchange*>(unit_you->getActions()->getAction(i)) )
                      {
                        Exchange * ex = dynamic_cast<Exchange*>(unit_you->getActions()->getAction(i));
                        for ( auto &itex: ex->getExchangeList() )
                          {
                            std::cout << "ITEM from list: " << std::endl;
                            std::cout << itex.first << std::endl;
                            std::cout << itex.second << std::endl;
                          }

                      }


                  }
                std::cout << "Main: Temporary button: There is nothing here" << std::endl;
              }
            }
          else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
              if (event.button.button == SDL_BUTTON_LEFT)
                {
                  //check if mouse collides with a button
                  Menu * menu_called = Menus->collide(event.button.x, event.button.y);
                  if ( menu_called != nullptr )
                    {
                      //true if menu is to be cleared (should probably move this into the child classes of menu
                      // that actually use it, like pop menu)
                      TerminalText::printTerminal("INFO: main: Mouse Button Down section: A menu has been clicked, calling it's outcome now.");
                      if ( menu_called->outcome() == true)
                        {
                          menu_called->setActive(false);
                          TerminalText::printTerminal("INFO: main: Mouse Button Down section: About to clear the PopMenu.");
                          menu_called->clear();
                        }
                    }
                  //remove menu if not clicked and on
                  else
                    {
                      if (Menus->isActive())
                        {
                          Menus->setAllNotActive();
                        }
                    }

                  //takes screen pos and gives tile coords
                  float pos_x = getIsoX(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
                  float pos_y = getIsoY(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);

                  if ((pos_x >= 0) and
                    (pos_y >= 0) and
                    (pos_x < map.mWidth) and
                    (pos_y < map.mHeight))
                    {
                      std::cout << "Click at: X=" << pos_x << " Y=" << pos_y << std::endl;
                      std::cout << "Click at: X=" << event.button.x << " Y=" << event.button.y << std::endl;
                    }
                }

              else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                  //pop_menu = Menus->getPopMenu();
                  if (pop_menu != nullptr)
                    {
                      float pos_x = event.button.x;
                      float pos_y = event.button.y;
                      Entity * target_entity;
                      //check for click on unit
                      target_entity = Units->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
                      if (target_entity == nullptr)
                        {
                          //check for click on building
                          target_entity = Buildings->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
                          if (target_entity == nullptr)
                            {
                              //check for click on Resource
                              target_entity = Resources->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
                            }
                        }
                      if (target_entity != nullptr )
                        {
                          std::cout << "You clicked in the region" << std::endl;
                        }
                      else
                        {
                          std::cout << "Clicked Nothing" << std::endl;
                        }

                      //make the pop menu for the available actions
                      //only make the pop_menu if no other menu is active
                      if ( !pop_menu->isActive() && !Menus->isActive() )
                        {
                          pop_menu->setXYPositions(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom);
                          if (target_entity != nullptr )
                            {
                              makeActionMenu(pop_menu, selected_entity, target_entity, info_menu, exchange_menu);
                            }
                          else
                            {
                              makeActionMenu(pop_menu, selected_entity);
                            }
                        }
                      else
                        {
                          pop_menu->clear();
                        }
                    }
                }
            }
          else if (event.type == SDL_MOUSEMOTION)
            {
              //takes screen pos and gives tile coords
              int pos_x = getIsoCoordinateX(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
              int pos_y = getIsoCoordinateY(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);

              sprite_selection->setPosX(pos_x);
              sprite_selection->setPosY(pos_y);
            }
          else if (event.type == SDL_MOUSEWHEEL)
            {
              if (event.wheel.y > 0 && scroll_active)
                {
                  if (zoom < 2.0)
                    {
                      //takes screen pos and gives tile coords
                      //int iso_x = getIsoCoordinateX(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom);
                      //int iso_y = getIsoCoordinateY(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom);
                      int iso_x = getIsoX(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
                      int iso_y = getIsoY(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);

                      //Zooming:
                      zoom += 0.25;

                      //Centering:
                      //takes tile coords and gives pixel coords
                      float pixel_x = getPixelX(iso_x, iso_y, 0,0, zoom, TILE_SIZE);
                      float pixel_y = getPixelY(iso_x, iso_y, 0,0, zoom, TILE_SIZE);
                      cameraoffset_x = (pixel_x + (TILE_SIZE*zoom)*0.5) - screen_width*0.5;
                      cameraoffset_y = (pixel_y + (TILE_SIZE*zoom)*0.75) - screen_height*0.5;
                    }
              }
            else if (event.wheel.y < 0 && scroll_active)
              {
                if (zoom > 0.26)
                  {
                    //takes screen coords and gives tile coords
                    //int iso_x = getIsoCoordinateX(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom);
                    //int iso_y = getIsoCoordinateY(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom);
                    int iso_x = getIsoX(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
                    int iso_y = getIsoY(screen_width/2, screen_height/2, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);

                    //Zooming:
                    zoom -= 0.25;

                    //Centering:
                    //takes tile coords and gives pixel coords
                    float pixel_x = getPixelX(iso_x, iso_y, 0,0, zoom, TILE_SIZE);
                    float pixel_y = getPixelY(iso_x, iso_y, 0,0, zoom, TILE_SIZE);
                    cameraoffset_x = (pixel_x + (TILE_SIZE*zoom)*0.5) - screen_width*0.5;
                    cameraoffset_y = (pixel_y + (TILE_SIZE*zoom)*0.75) - screen_height*0.5;
                  }
            }
            }
        }

      //-------------------------------------------------------------------------------------
      // Rendering: The Order Here Matters
      //-------------------------------------------------------------------------------------

      //TerminalText::printTerminal("INFO: main: Rendering Section: Now beginning rendering.");

      SDL_RenderClear(renderer);

      map.render(cameraoffset_x, cameraoffset_y, zoom);

      sprite_selection->render(cameraoffset_x, cameraoffset_y, zoom);

      //vill->render(cameraoffset_x, cameraoffset_y, zoom);

      //std::cout << "INFO: Before rendering EntityGroup" << std::endl;
      Units->render(cameraoffset_x, cameraoffset_y, zoom);
      //std::cout << "INFO: After rendering EntityGroup" << std::endl;

      //render resources
      Resources->render(cameraoffset_x, cameraoffset_y, zoom);

      //render resources
      Buildings->render(cameraoffset_x, cameraoffset_y, zoom);

      //render menu
      Menus->render(cameraoffset_x, cameraoffset_y, zoom);

      //render Temp text
      //message->render();

      if (use_custom_cursor)
        {
          renderTexture(texture_cursor, renderer, mouse_x, mouse_y);
        }

      SDL_RenderPresent(renderer);

      //FPS:
      float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
      ++countedFrames;

      if (!VSYNC_ACTIVE)
        {
          int frameTicks = capTimer.getTicks();
          if (frameTicks < SCREEN_TICKS_PER_FRAME)
            {
              SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
            }
        }


      //Window title:
      if (debug_mode)
        {
          int pos_x = getIsoCoordinateX(mouse_x, mouse_y, cameraoffset_x, cameraoffset_y, zoom);
          int pos_y = getIsoCoordinateY(mouse_x, mouse_y, cameraoffset_x, cameraoffset_y, zoom);

          std::stringstream ss;
          ss << "IsoMap";
          ss << " | mouse: " << mouse_x << " " << mouse_y;
          ss << " | coordinates: " << pos_x << " " << pos_y;
          ss << " | cameraoffset: " << cameraoffset_x << " " << cameraoffset_y;
          ss << " | zoom: " << zoom;
          ss << " | avgFPS: " << int(avgFPS);
          ss << " | vsync: " << VSYNC_ACTIVE;
          const std::string tmp = ss.str();
          const char *title = tmp.c_str();
          SDL_SetWindowTitle(window, title);
        }
      else
        {
          SDL_SetWindowTitle(window, "IsoMap");
        }

        //TerminalText::printTerminal("INFO: main: Rendering Section: Finished rendering.");

    }

  //-------------------------------------------------------------------------------------
  //Cleanup:
  //-------------------------------------------------------------------------------------
  delete sprite_selection;
  delete TextHandler;
  delete Units;
  delete Resources;
  delete Buildings;
  delete Menus;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();

  return 0;
}
