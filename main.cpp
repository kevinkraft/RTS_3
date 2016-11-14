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
// * Add a menu function that display things about an entity
//   * like its hp, name, pos and inventory
//   * need to add some text table functions to menus(done)
//   * add a sort of Action called Info which will appear in the pop_menu and display the info_menu 
//     populated for that entity(done)
// * exchange action
//   * need a text input menu or box first(skip)
//     * do a quick demo in the main loop, done in SDLExamples (done)
//     * I don't want to get stuck doing this, so just use buttons to add the number of an item you
//       want to transfer (ok)
//   * this will require an exchange interface to decide what to exchange
//   * will have a list of pairs of item type int and amount to exchange
//   * the action will involve a rate at which things are exchanged
//   * need a menu with two text boxes and a button beside each entry to select
//     * make a menu derived class caled SelectionMenu to do this
//       * will contain buttons and list of text items
//       * the button outcome and text must match somehow
//       * the button outcome will make the desired class selected and return it
//       * will have to make Item and Entity and anything else that you can put in a selectin list 
//         inherit from the same class (done)
//       * test this by using it to switch the selected_entity
//         * it's outcome needs to come back when Menus->outcome is called
//         * but it can't exist before it's needed as the other menus do as this is not a unique menu
//           there may be many instances of SelectionMenu
// * Low Priority:
//   * InfoMenu
//     * it would be nice if the InfoMenu updated in real time

//Problem:
// * seg fault when consctucting the SelectionMenu
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
//   * I will have to tune the line height so that it works, but this will change if the font size changes

//-------------------------------------------------------------------------------------      

#include <iostream>
#include <string>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

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
  Unit * unit_you = new Unit(0., 0., "You");
  Unit * unit1 = new Unit(4.5, 4.5, "Unit1");
  EntityAction * selected_entity = unit_you;
  //Movement * move1 = new Movement(10., 8.);
  //unit_you->appendAction(move1);
  Movement * move2 = new Movement(0., 0.);
  unit1->appendAction(move2);
  //Attack * attack = new Attack(unit1);
  //unit_you->appendAction(attack);

  //make a group to hold units
  EntityGroup * Units = new EntityGroup(renderer, window);
  Units->addEntity(unit_you);
  Units->addEntity(unit1);

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

  //make a food item and give it to the unit
  Item* food1 = new Item(1., 5.);
  Item* wood1 = new Item(2., 1.);
  unit_you->addItem(food1);
  unit_you->addItem(wood1);
  unit_you->printInventory();
  Item* food2 = new Item(1., 5.);
  unit1->addItem(food2);

  //make buildings
  //make a group to hold buildings
  EntityGroup * Buildings = new EntityGroup(renderer, window);
  Building * hut = new Building(3., 3., 0);
  Buildings->addEntity(hut);
  
  //make a menu
  InfoMenu * info_menu = new InfoMenu(renderer, window, TextHandler);
  info_menu->setActive(false);
  Menus->addMenu(info_menu);

  //TEMP
  /*  Menu * sel_menu = new Menu(0, 0, 500, 600, renderer, window, TextHandler);;
  SelectionMenu * sl = new SelectionMenu(0, 0, 1, 1, sel_menu, Units );
  sel_menu->addSelectionMenu( sl );
  Menus->addMenu( sel_menu );*/
  

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
      Units->update();
      Resources->update();
      Buildings->update();

      //-------------------------------------------------------------------------------------      
      // Entity operations
      //-------------------------------------------------------------------------------------      
      Units->doActions();
      Buildings->doActions();
      
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
	      else if (event.key.keysym.sym == SDLK_t)
		{
		  /*if ( sel_menu->isActive() == false )
		    sel_menu->setActive(true);
		  std::cout << "Main: Temporary button: There is nothing here" << std::endl;
		  //temporary testing
		  std::cout << "INFO: main: sel_menu has buttons: " << sel_menu->getSizeButtons() << std::endl; 
		  std::cout << "INFO: main: sel_menu has text boxes: " << sel_menu->getSizeTextBoxes() << std::endl; 
		  std::cout << "INFO: main: sel_menu has selection menus: " << sel_menu->getSizeSelectionMenus() << std::endl;
		  }*/
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
		      if ( menu_called->outcome() == true)
			{
			  menu_called->setActive(false);
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
			      makeActionMenu(pop_menu, selected_entity, target_entity, info_menu);
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
