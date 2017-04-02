//Main implementation and game loop
//
//Kevin Maguire
//18/08/15
//
//Version 0.6
//

//Add:
// * stockpile
//   * so beginnings of building class
//     * add a unit inventory to building
//     * be careful, the default range and att damage of an EntityAction is set to the unit values, need to fix
// * collect resource action
//   * need to do exchange action first
// * Add a menu function that display things about an entity(done)
//   * like its hp, name, pos and inventory(done)
//   * need to add some text table functions to menus(done)
//   * add a sort of Action called Info which will appear in the pop_menu and display the info_menu(done)
//     populated for that entity(done)
// * exchange action
//   * Needs to be tested, its not clear if its working due to the problems with InfoMenu
//     * is the ExchangeMenu ExchangeList cleared between exchanges? (yes it is, len of exchange list is zero during and after exchange)
//     * Is the exchange menu list passed to the exchange action correctly? (yes, tested with temp button output)
//     * If you press the close button it just opens itself again (fixed)
//       * made a new close button, and a new attribute mWasClosed(ok)
//     * It seems that the exchange speed isn't being accounted for, or is it?(yes it is)
//     * When you try a second exchange, the menu doesn't come up, I need to clear the old menu somewhere(fixed)
//       * it gets cleared in loads of places, its a bit confusing, but its working now(ok)
//     * Various issues with the action itself:(all fixed)
//       * I had an entity with 8 in its inventory and could give it more, inv cap is 10 though?(ok)
//         * this is desired behaviour, wood has unit size of 3. add inv size to info menu(ok)
//         * unit had 7 food and 1 wood, I was trying to give it one more wood.(ok)
//       * Exchanging wood doesn't work? Value is never removed from acter(fixed)
//         * its always duplicated and never reaches the final value, 0.93 instead of 1.(ok)
//         * this seems to be the same issue as the one below.(its that issue plus another one)
//         * the duplication was the same as the issue below. Not completely finishing the exchange is another issue(ok)
//           * it probably stops too early for some reason.(yes)
//           * changing the 0.01 tolerance doesnt change anything (ok)
//           * why isnt food exchange also affected? (food is also affected)
//           * this problem only occurs sometimes?(problem found)
//             * related to having two items in the inventory? (no, also happens with one)
//             * its when the acters inventory goes to zero(ok)
//           * fixed it, there were some extra ccontinue commands after the item was removed from the acter and before it was(fixed)
//             given to the target(fixed)
//       * The first food exchange works fine, but subsequent ones do not, the value is duplicated as with wood.(fixed)
//         * I think these issues are related to exchanging with a unit which doesn't have the item already, so the(ok)
//           problem occurs when the unit doesnt already have some of the item its recieveing.(ok)
//           * I verified this by exchanging wood to a unit that already had wood, it works fine. (ok)
//           * Exchanges with negative amounts seem to be fine in this respect(ok)
//           * I think I found the problem, the acter_item is given to the target where the target item should be given(yes)
//             * yes this was the problem(ok)
//       * exchanges with negative amounts leave a little bit left over in the targets inventry, about e-7.(fixed)
//         * such a small number indicates amount = null, so maybe the empty item isnt deleted.(ok)
//         * was this fixed by changing the tolerance to delete items from 0 to 0.01?(yes, think so)
//       * The action gets stuck and just loops when amount is negative and the target doesnt have enough?(fixed already)
//         * I can replicated this, but only sometimes(cant replicate)

//   * currently the acter can give more than it has( this isnt true, or is fixed)
//   * giving a negative amount to the target doesnt exchange things the other way, as it should (fixed, needed abs(amount))
//   * The target also can give more than it has available(fixed)
//   * the inventory cap isn't accounted for in exchange(done)
//     * add this(done)
//     * also add the exchange speed and the inv cap to the info menus(done)
//   * make the action base first(done)
//     * the action will involve a rate at which things are exchanged(done)
//     * also a list of pairs of item number and amount to exchange(done)
//     * it will need an acter and a target,  both must be EntityActions so that they have inventories(acter must be unit)
//   * need a text input menu or box first(skip)
//     * do a quick demo in the main loop, done in SDLExamples (done)
//     * I don't want to get stuck doing this, so just use buttons to add the number of an item you(ok)
//       want to transfer (ok)
//   * this will require an exchange interface to decide what to exchange(done)
//     * will have a list of pairs of item type int and amount to exchange(done)
//     * the exchange action, when called from the pop menu will make an exchange menu.(done)
//       The exchange menu will recieve the choice, pass it to the action, which will then doAction.(done)
//       * The makeExchange function has to make an ExchangeMenu(done)
//         * where is the acter set when the pop menu is used? I dont know!! (its in pop menu)
//   * need a menu with two text boxes and a button beside each entry to select(done)
//     * now need to make an exchange menu(done)
//       * will contain a selection sub menu and a way to choose the amount, with arrow buttons(done)
//     * make a SubMenu derived class called SelectionMenu to do this (done)
//       * will contain buttons and list of text items (done)
//       * the button outcome and text must match somehow (done)
//       * the button outcome will make the desired class selected and return it(done)
//       * will have to make Item and Entity and anything else that you can put in a selectin list(done)
//         inherit from the same class (done)
//       * test this by using it to switch the selected_entity (done)
//         * it's outcome needs to come back when Menus->outcome is called (it's selected entity is called where the entity groups are updated)
//         * but it can't exist before it's needed as the other menus do as this is not a unique menu(ok)
//           there may be many instances of SelectionMenu (ok)
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
// * AFTER MAKING THE EXCHANGE MENU THE INFO MENU NO LONGER WORKS (fixed)
//   * some warnings before its called.(not the problem)
//     * WARN: In Action::setActer. (not a problem)
//       * This is expected behaviour. The InfoAction has no setActer function as it only requires a target. so(ok)
//         it uses the base Action::setActer function, which does nothing. this is fine (ok)
//     * Entity::actionsOnMe: WARN: This function should not be called, this error has dissappeared, it should give an error message anyway, fixed (ok)
//   * something to do with the pop menu, and the actions?(no)
//   * something to do with clearing the PopMenu? (no)
//   * Switching the "Info" and "Exchange" buttons in the PopMenu doesn't change or fix the issue (ok)
//   * The problem was this: InfoMenu is wiped before it is populated, Menu::wipe() calls TextBox::setWords(""). This function works fine with
//     a blank string, but I had placed a print command "lines[0]" while debugging the Exchange Action, but an empty string has no split chars,
//     so there are no lines to print and so it segfaults (ok)
// * If you right click, the pop menu comes up, if you then left click off the menu and right click again the buttons are duplicated
//   * It essentially allows you to have commands related to two different coords/entities in the same pop menu
// * seg fault when constructing the SelectionMenu (fixed)
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
// * The number box textbox doesnt work
//   * This is due to problems with TextBox I think.
//     * it seems that changing the text in a TextBox breaks the TextBox. It seems that the new text
//       exists and it looks like it is rendered, but I cant see it. Maybe it is being rendered behind
//       the menu for some reason? Menu has non pointer members like mTextBoxes, I think these should be
//       pointers, it's possible I'm asscessing the mTextBoxes of the parent Menu rather than the SubMenu
//       child in NumberBox when I do mTextBoxes[0]. I tried to replace mTextBoxes with pointers, but there was
//       a seg fault in TextBox
//   * I think I fixed it, I just need to set the updated text box active, it must turn it off somewhere.
//     * It makes a new list of text lines which are all default not active
//

//Cross Platform Problems:
// * The building sprite doesn't appear, but the entity is there and can be clicked
//   * the building and sprite positions are correct, 3 and 3 for the first bui;ding in the list
//   * The problem is simply that the hut image is missing on github. Only 0.png is on github, but the game
//     uses o_2.png. I tried using 0.png but it looks weird, parts of it are see through, so don't change anything
//     and add the correct png to the repo
// * The map isn't generated randomly, its always the same(fixed)
//   * This is due to the new function I use as a random seed in map and resource class(fixed)

//-------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>

#include <SDL.h>
//#include <SDL2_image/SDL_image.h>
//#include <SDL2_ttf/ttf.h>

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
