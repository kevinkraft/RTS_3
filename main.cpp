//Main implementation and game loop
//
//Kevin Maguire
//18/08/15
//
//Version 1.0
//

//Add:
// * Add Nation class for holding the Nations, and updating/rendering Contained Entities etc.
// * Add Organisations, which allow you to make a group of Units and give them all commands
//   * Giving the Organisation leader a command will make that Unit give the same command to all Units
//     it it's Organisation
// * Add Order, the way in which the player, unit_you, can tell the other Units what to do.
// * Add functions which add a new region if a Unit walks off the edge of the map
// * Add Procreate action
// * Add Construct action, for building new Buildings
//   * If I'm going to do this, I need some buildings that are worth building(done)
//     * Make the hut inventory really small and make it necessary to construct a Stockpile(done)
//       * In Town::update, add some code which sets the stockpile to the Building with the(done)
//         largest inventory, or make it look for a Building of type==stockpile.(done, looks for type==1)
//   * Make a Stockpile building type(done)
//   * Make a child Class of EntityAction called Construction
//     * This class should not inherit from the Building class, that will probably cause problems(ok)
//     * Construction has some container telling you how much of certain types of items it needs(done)
//     * Will have to add this info to the Construction InfoMenu(done)
//     * It also has an amount of work that has to be done for it to be finished
//       * Units will need an atribute saying how much work they can do in each cycle
//     * When it's finished it is removed and a Building is put in its place.
//       * Might be difficult to add this to the Town building list
//     * Will need a Construt action to go with this
//       * This action will need some sort of menu for selection which building to build
//         * Use a selection menu, try to do it without making a dedicated menu
//       * Two ways to make this action
//         * This action can be made with a int Construction type, so that the construction can be first made
//         * Or this action can  be made with a preexisting target construction for the Unit to work on
//         * So you can make this action by clicking on a random patch of ground, or by clicking on a prexisting
//             Construction
//       * The Units will put items into the Constructions inventory
//       * When the construction is updated it will remove the items in its inventory from the materials map
//         and delete the items in its inventory
//       * So first step for the Units is to bring the necessary resource, so just setup an Exchange
//       * Then the Units decrase the Construction Work by some amount
//       * The trasnformation of the Construction into a Building will be handled by the Constructions update function
//         * will need to make a building, add it to the Town building list, then remove the construction from the town
//           construction list, then delete itself.
//   * First make a Wood Resource type that can be collected.(done)
//     * Need to move the code in Map that places the trees to somewhere else(done)
//     * Need to change the wood Resource sprite to be smaller(done)
// * Add a base entity container class(done)
//   * make a base class which runs update, render, doActions and collide on a set of contained entities(done)
//     * All Containers would inherit from this class, including Nation, when it exists and Region, Town.(done)
//     * It could contain a map of string and Entity Group, where the string is the identifier for a certain EntityGroup(done)
// * Eat action(done)
//   * Need to give the Units a Hunger attribute(done)
//     * when their hungry gets to some max they start to take damage(done)
//     * Maybe I should implement the UnitStatus class, which will hold Hunger, Loyalty, Happiness etc. (no)
//     * What should it be called? UnitStatus, Emotions? Why is it a separate class from Unit? (it doesnt need to be at this time)
//   * Action should not appear in the PopMenu, it is an automatic action(ok)
//   * write the action code(done)
//     * they eat food until their hunger is full(done)
//       * need an eat speed (no, make it instant)
//       * the food comes out of their inventories
//       * need a global for how much some amount of food decreases the hunger(done)
//     * If they have no food in their inventory they go to the stockpile(done)
//     * If there is no food in the stockpile they go and collect food from the nearest resource(done)
//       * Will need to have the list of Resources, this will be tricky(done)
//         * The list of Resources is now obtained from unit->town->region->mContainerList["resources"] (ok)
//         * Make a Region class which contains a list of Towns and a list of Resources(done)
//           * Setup the part in Region that populates the list of Resources(done)
//           * Setup the part which renders the map segments(done)
//           * The Town will need to know which region it is in(done)
//           * The region will also contain a Map segment(done)
//             * To test this I will need to make at least two regions, each with one town and a map(done)
//             * The Map class will need to know the top croner x and y positions of the region to know where it should be put on the screen(done)
//               * this is decided in the map constructor, we can either change it in the constructor or change it at render(in constructor)
//                 * change it in the constructor(done)
// * Collect action(done)
//   * Make unit find the next Resource if this one is empty(done)
//     * set the Target to nullptr if its amount is empty(done, but not this way)
//     * write code to search for another of the same type if the Target pointer is empty(done)
// * collect resource action(done)
//   * make the action itself(done)
//      * add it to the entity available action(done)
//      * write the doAction code(done)
//        * will need to move to the resource.(done)
//        * then collect the resource item, which is different from exchange(done)
//        * then move to the stockpile(not necessary)
//        * then do an exchange with the stockpile(done)
//        * then repeat.(done)
//   * instead of a stockpile just use the hut.(ok)
//   * Make a Town class, which is a container for the buildings and units, allows for functions to be run on all these(done)
//     entites in a loop, and can be used for more complicated relations later.(done)
//     * What are Towns atributes?(done)
//       * BuildingList, EntityList, Stockpile(done)
//       * Need to duplicate the Update, Render and doAction functions for Town(done)
//     * The EntityGroups for buildings and units belong to the town(done)
//     * The EntityActions in the Building and Units EntityGroups know which Town they are in(done)
//       * In this way, the Units know which building is the towns stockpile and know where to bring their collected items.(ok)
// * Low Priority:
//   * InfoMenu
//     * it would be nice if the InfoMenu updated in real time
//   * Exchange
//     * Fix the "once" options so that the Unit actually gives its items to the stockpile

//Problem:
// * There was a seg fault shortly after the Stockpile construction was finished
//   * can it be replicated?
// * The Construct action got into an infinite loop
//   * happened when Constructing the Stockpile, when many Units were working, possibly to do with the Eat action
//   * Can it be replicated?
// * If you open an InfoMenu, press a down scroll, close it and open another, the game seg faults(fixed)
//   * So the scroll state of the info menu needs to be reset when you close it / clear it. (yes)
//   * fixed by resetting mScroll of the TextBox to zero when calling Menu::wipe() (ok)
// * If a Unit from one region goes into another region the other Region map is rendered on top of him(fixed)
//   * need to setup the Region container thing to render all the maps first(done)
// * Adding food to the hut00 inventory when making the objects doesn't actually add food to the inventory(fixed)
//   * It works after the setstockpile Town function, so the problem must be there.(fixed)
//   * The problem is that setupType for Resource and Building are not called in their constructors but are called when you(ok)
//     add them to an entity group. So the hut has zero inv cap the first time you try to add the item (ok)
//   * I fixed this by calling setupType in the Building constructor, and also did it for the Resource(ok)
//   * I remove the setupType call in the EntityGroup::addEntity function and the entities no longer appear on the map(fixed)
//     * why is this? they should already be setup after they are constructed, so why is it necessary to do it again?(fixed)
//     * the buildings and Resources are not rendered, but they are clickable. Units are rendered correctly(ok)
//       * So the sprite is not being set in the entity group, or the sprite is blank(yes)
//       * It might be because a new blank sprite is made by the Entity constructor, so the sprite setup by the Building(yes)
//         setupType function is overwritten.(yes)
//         * The bes way to fix this is to have setupType called twice, once in the Building constructor and once by the (ok)
//           EntityGroup(ok)
// * Fix the Sprite click boxes after adding new sprites
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
//   * Can also replicate this straight away by setting the map size to be really big, 100 for example
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
#include <random>
#include <ctime>

#include <SDL.h>

#include "global.h"
#include "logging.h"
#include "Timer.h"
#include "Sprite.h"
#include "SpriteGroup.h"
#include "Region.h"
#include "Town.h"
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
#include "Construction.h"
#include "Construct.h"

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
  std::cout << "Main: INFO: Starting To Make Objects" << std::endl;

  //misc objects
  SDL_Texture *texture_cursor  = loadTexture("res/images/cursor.png", renderer, false);
  Sprite *tile_hover = new Sprite("res/images/iso/selection.png", 2, 2, renderer, window, TILE_SIZE);

  //Make the Towns, 00 = region 0, town 0
  Town * town00 = new Town("Town00", renderer, window);
  Town * town01 = new Town("Town01", renderer, window);
  Town * town10 = new Town("Town10", renderer, window);

  //make buildings and add to the Towns as the stockpile
  Building * hut00 = new Building(1., 1., 0);
  Item * hut00_food = new Item(1,50.);
  hut00->addItem(hut00_food);
  Building * hut01 = new Building(floor(1.+MAP_SIZE/2.), floor(1.+MAP_SIZE/2.), 0);
  Building * hut10 = new Building(1.+MAP_SIZE, 1., 0);
  town00->setStockpile(hut00);
  town01->setStockpile(hut01);
  town10->setStockpile(hut10);

  //make a dedicated stockpile Building
  Building * stockpile00 = new Building(1., 3., 1);
  town00->addEntity(stockpile00);

  //Make the Units, give Items to some, give Moovement to one, and add to the Towns
  //also set one of the other units to attack "you"
  Unit * unit_you = new Unit(2., 2., "You");
  Item * unit_you_food = new Item(1,1.);
  unit_you->addItem(unit_you_food);
  //Item * unit_you_wood = new Item(2,1.);
  //unit_you->addItem(unit_you_wood);
  EntityAction * selected_entity = unit_you;
  town00->addEntity(unit_you);
  Unit * unit_loop;
  std::string uloop_name = "";
  for (int i = 0; i<5; i++)
    {
      std::stringstream n_ss;
      n_ss << "Unit00" << i;
      uloop_name = n_ss.str();
      unit_loop = new Unit(hut00->getPosX()+2, hut00->getPosY()+i*0.5+2, uloop_name);
      if (i == 0)
        {
          Item* food = new Item(1., 1.);
          Item* wood = new Item(2., 1.);
          unit_loop->addItem(food);
          unit_loop->addItem(wood);
        }
      if (i == 1)
        {
          Movement * move = new Movement(3., 3.);
          unit_loop->clearAddAction(move);
        }
      town00->addEntity(unit_loop);
    }
  for (int i = 0; i<5; i++)
    {
      std::stringstream n_ss;
      n_ss << "Unit01" << i;
      uloop_name = n_ss.str();
      unit_loop = new Unit(hut01->getPosX()+2, hut01->getPosY()+i*0.5+2, uloop_name);
      if (i == 0)
        {
          Item* food = new Item(1., 1.);
          Item* wood = new Item(2., 1.);
          unit_loop->addItem(food);
          unit_loop->addItem(wood);
        }
      town01->addEntity(unit_loop);
    }
  for (int i = 0; i<5; i++)
    {
      std::stringstream n_ss;
      n_ss << "Unit10" << i;
      uloop_name = n_ss.str();
      unit_loop = new Unit(hut10->getPosX()+2, hut10->getPosY()+i*0.5+2, uloop_name);
      if (i == 0)
        {
          Item* food = new Item(1., 1.);
          Item* wood = new Item(2., 1.);
          unit_loop->addItem(food);
          unit_loop->addItem(wood);
        }
      /*if ( i == 1 )
        {
          Attack * attack = new Attack(unit_you);;
          unit_loop->appendAction(attack);
        }*/
      town10->addEntity(unit_loop);
    }

  //TEMP make constructions
  //Construction * stockpile_constr = new Construction(1., 5., 1);
  //town00->addEntity(stockpile_constr);
  Construction * hut_constr = new Construction(1., 7., 0);
  town00->addEntity(hut_constr);

  //TEMP set unit_you to work on the construction
  Construct * construct = new Construct(hut_constr);
  //unit_you->clearAddAction(construct);

  //Make random number generators for the Region seeds
  std::default_random_engine RGen(time(NULL));
  std::uniform_int_distribution<int> RandGen(0, 1000000);

  //Make the Regions which also make the map segments and food Resources, add the towns
  Region * region0 = new Region("Region0",0, 0, MAP_SIZE, MAP_SIZE, RandGen(RGen), renderer, window);
  Region * region1 = new Region("Region1",MAP_SIZE, 0, MAP_SIZE, MAP_SIZE, RandGen(RGen), renderer, window);
  region0->addTown(town00);
  region0->addTown(town01);
  region1->addTown(town10);

  //Make a container for the Region classes and add the Regions
  EntityContainer * Regions = new EntityContainer("Regions", renderer, window );
  Regions->addContainer("regions", region0);
  Regions->addContainer("regions", region1);

  //Set the image filename of the Unit group
  town00->setUnitImage("res/images/units/villager.png");
  town01->setUnitImage("res/images/units/villager.png");
  town10->setUnitImage("res/images/units/villager.png");

  //Make a TextMaker
  TextMaker * TextHandler = new TextMaker("res/fonts/KaushanScript-Regular.otf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/Pacifico.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/FFF_Tusj.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/sample.ttf", renderer, window);

  //Make a menu group
  MenuGroup * Menus = new MenuGroup();

  //Make the pop_menu
  PopMenu * pop_menu = new PopMenu(renderer, window, TextHandler);
  Menus->addMenu(pop_menu);

  //Make other menus
  InfoMenu * info_menu = new InfoMenu(renderer, window, TextHandler);
  info_menu->setActive(false);
  Menus->addMenu(info_menu);
  ExchangeMenu * exchange_menu = new ExchangeMenu(renderer, window, TextHandler);
  exchange_menu->setActive(false);
  Menus->addMenu(exchange_menu);

  //Make the unit selection menu, which is a developer tool
  Menu * unit_sel_menu = new Menu(0, 0, 500, 600, renderer, window, TextHandler);
  unit_sel_menu->makeCloseButton();
  SelectionMenu * sl = new SelectionMenu(0, 0.05*unit_sel_menu->getHeight(), 1, 0.95, unit_sel_menu, town00->getUnits() );
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
      // Entity operations
      //-------------------------------------------------------------------------------------
      //TerminalText::printTerminal("INFO: main: Actions Section: About to do the Unit actions.");
      Regions->doActions();
      //TerminalText::printTerminal("INFO: main: Actions Section: Finished the Entities actions.");

      //-------------------------------------------------------------------------------------
      // Update Entity states
      //-------------------------------------------------------------------------------------
      //TerminalText::printTerminal("INFO: main: Updates Section: About to update the entities.");
      Regions->update();
      //Resources->update();
      if ( unit_sel_menu->isActive() == true && unit_sel_menu->getSelectionMenu(0)->hasSelection() == true)
        selected_entity = dynamic_cast<EntityAction*>(unit_sel_menu->getSelectionMenu(0)->getSelection());

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
                region0->getMap()->setDrawGrid( not(region0->getMap()->getDrawGrid()) );
                region1->getMap()->setDrawGrid( not(region1->getMap()->getDrawGrid()) );
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
                TerminalText::printTerminal("INFO: main:temp button: Stockpile of town00 is "+(town00->getStockpile()->getName())+" ");
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
                    (pos_x < region0->getMap()->mWidth) and
                    (pos_y < region0->getMap()->mHeight))
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
                      //check for click on Town Units or Buildings
                      target_entity = Regions->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
                      /*if (target_entity == nullptr)
                        {
                          target_entity = Resources->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
                        }*/
                      if (target_entity != nullptr )
                        {
                          std::cout << "INFO: main: Right Click section: You clicked in the region." << std::endl;
                        }
                      else
                        {
                          std::cout << "INFO: main: Right Click section: Clicked Nothing." << std::endl;
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

              tile_hover->setPosX(pos_x);
              tile_hover->setPosY(pos_y);
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

      //Render everything contained in the Regions, map segments, buildings, entities
      //need a special render function for te Regions so that the Maps are rendered before any
      //of the Entities, this bit of code can be added to the Nation container class when I eventually make it
      for ( int i=0; i < Regions->getContainerGroup("regions")->size(); i++)
        {
          dynamic_cast<Region*>(Regions->getContainerGroup("regions")->at(i))->getMap()->render(cameraoffset_x, cameraoffset_y, zoom);
        }
      Regions->render(cameraoffset_x, cameraoffset_y, zoom);

      //Render the transparent hovering square
      tile_hover->render(cameraoffset_x, cameraoffset_y, zoom);

      ////Render resources
      //Resources->render(cameraoffset_x, cameraoffset_y, zoom);

      //render menus
      Menus->render(cameraoffset_x, cameraoffset_y, zoom);

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
  delete tile_hover;
  delete TextHandler;
  delete Regions;
  //delete Resources;
  delete Menus;

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();

  return 0;
}
