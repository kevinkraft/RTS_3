//Main implementation and game loop
//
//Kevin Maguire
//18/08/15
//
//Version 0.2
//

//Add:
// * make actionMenu and actionButton classes to contain all that messy action stuff in menu and button
//   * separate button menu and action, the actions should have nothing to do with buttons
// * do the other actionsBy/On functions so that its not just move available in the pop menu
// * Rewrite texture.cpp so that it doent use TILE_SIZE, this messes with the other sprites
// * Text on buttons
//   * need to pass TextHander to the classes that need text (button, menu) somehow
//     * maybe use a global class
//     * or define it as a property of menu and button
//   * need to set the position of the message on the button at render time

//Problem:
// * When you add a second button to the pop menu it doesnt print a second button
//   it just prints a longer first button
//   * this may just be a consequence of the testing that I'm currently doing
//   * Its probably cause by the rel width/length given to the buttons
//     * its set to 1 so if there is more than one button the buttons are still
//       the same size as the menu
//     * I thought my fix would work but it didnt
//     * Oh it probably did work, but the menu thinks there only one button because
//       the rel height is done in makeActionMenu which only knows about one buton
//     * its a symptom of how I am currently testing the code
// * The dependence on TILE_SIZE in the coord mapping functions is wrong(fixed)
//   * only the tiles should depend on tile size
//   * need to have a scale in that function which is only TILE_SIZE if a tile is being printed
//   * I replaced TILE_SIZE with scale=1. now it just works
//     * zoom out(I think its zoom out thats broken not zoom in) is not working properly, it shifts the screen down
//     * it was both, fixed by added the TILE_SIZE as a scale option
//     * ANYTHING TO DO WITH THE ACTUAL MAP NEEDS TILE_SIZE, MAYBE EVEYTHING TO DO WITH MOUSE TOO
// * The sprite clicking box isnt on the sprite
//   * its done with an x and y tolerance so the box is isometric as the map is, while
//     the sprite standes upright at 45 degrees to the grid lines
//     * this should really be pixel coords
//       * maybe give the sprite pixel coords also, issues with not knowning the screen config
//   * The problem is that the image of the villager is larger than it seems
//     * this is not what I want to be doing, just go back to the way it was an apply an offset to make it work
//     * I need to re do texture and sprite so that the sprite has a rectangle and the image is blinted into the rectange
//       * make a new texture function that just updates a preexisting rectangle
//     * then I can simply do collision with that rect.(no)


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
#include "Menu.h"
#include "PopMenu.h"
#include "MenuGroup.h"
#include "Map.h"
#include "Action.h"
#include "TextMaker.h"
#include "Message.h"

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
  
  SpriteGroup *spritegroup_main = new SpriteGroup(renderer, true);
  Sprite *sprite_selection = new Sprite("res/images/iso/selection.png", 2, 2, renderer, window, TILE_SIZE);

  /*//move a sprite (not an entity)
  float villx = 2.5;
  float villy = 2.5;
  Sprite *vill = new Sprite("res/images/units/villager.png", villx, villy, renderer, window);*/

  //make an entity and move it
  Unit * unit_you = new Unit(2.5, 2.5, "You");
  EntityAction * selected_entity = unit_you;
  //Unit * unit1 = new Unit(4.5, 4.5, "Unit1");
  //Movement * move = new Movement(10., 8.);
  //unit_you->appendAction(move);
  //Movement * move = new Movement(0., 0.);
  //unit1->appendAction(move);
  //Attack * attack = new Attack(unit1);
  //unit_you->appendAction(attack);

  //make a group to hold units
  EntityGroup * Units = new EntityGroup(renderer, window);
  Units->addEntity(unit_you);
  //Units->addEntity(unit1);

  //set the image filename of the group
  Units->setImage("res/images/units/villager.png");

  //make a text maker
  TextMaker * TextHandler = new TextMaker("res/fonts/KaushanScript-Regular.otf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/Pacifico.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/FFF_Tusj.ttf", renderer, window);
  //TextMaker * TextHandler = new TextMaker("res/fonts/sample.ttf", renderer, window);
  
  //make a temp message
  Message * message = new Message(3., 3., 500., 50., "HELLO WORLD RTS 3", TextHandler);
  message->setActive(true);
  
  //make a pop_menu
  PopMenu * pop_menu = new PopMenu(renderer, window, TextHandler);
  pop_menu->loadImage("res/images/menu/menu.png");


  //make a menu group
  MenuGroup * Menus = new MenuGroup();
  Menus->addMenu(pop_menu);

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

      //-------------------------------------------------------------------------------------      
      // Entity operations
      //-------------------------------------------------------------------------------------      
      Units->doActions();
      
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
		  //temporary testing
		  //std::cout << "Main: INFO: In temporary testing " << std::endl;
		  if (pop_menu != nullptr)
		    {
		      //TEMP
		      pop_menu->getButton(1)->setPressed(true);
			//TEMP
		      pop_menu->outcome();
		    }
		  pop_menu->setActive(false);
		  pop_menu->clear();
		}
	    }
	  else if (event.type == SDL_MOUSEBUTTONDOWN)
	    {
	      if (event.button.button == SDL_BUTTON_LEFT)
		{
		  //THIS WILL BE A PROBLEM FOR CLICKING ON THE MENUS AS CLICKING IS BELOW THIS
		  //remove menu if its on
		  if (Menus->isActive())
		    {
		      Menus->setAllNotActive();
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

		      //float pos_x = getIsoX(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
		      //float pos_y = getIsoY(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);		      
		      float pos_x = event.button.x;
		      float pos_y = event.button.y;
		      Entity * target_entity = Units->collide(pos_x, pos_y, cameraoffset_x, cameraoffset_y, zoom);
		      if (target_entity != nullptr )
			{
			  std::cout << "You clicked in the region" << std::endl;
			}
		      else
			{
			  std::cout << "Clicked Nothing" << std::endl;
			}
		   

		      //THIS IS NOT TEMPORARY DO NOT DELETE
		      //std::cout << "Main: INFO: Pop menu mButtons length: " << pop_menu->getSizeButtons() <<std::endl;
		      /*if ( !pop_menu->isActive() )
			{
			  
			  //temporary test of "clicking on" another entity
			  pop_menu->setPositions(event.button.x, event.button.y, cameraoffset_x, cameraoffset_y, zoom);
			  //makeActionMenu(pop_menu, selected_entity);
			  Unit * target_entity = unit1;
			  makeActionMenu(pop_menu, selected_entity, target_entity);
			}
		      else
			{
			  pop_menu->clear();
			  }*/
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
	      if (event.wheel.y > 0)
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
	      else if (event.wheel.y < 0)
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
      // Rendering:
      //-------------------------------------------------------------------------------------
      SDL_RenderClear(renderer);

      map.render(cameraoffset_x, cameraoffset_y, zoom);
      
      sprite_selection->render(cameraoffset_x, cameraoffset_y, zoom);
      
      //vill->render(cameraoffset_x, cameraoffset_y, zoom);
      
      spritegroup_main->render(cameraoffset_x, cameraoffset_y, zoom);

      //std::cout << "INFO: Before rendering EntityGroup" << std::endl;
      Units->render(cameraoffset_x, cameraoffset_y, zoom);
      //std::cout << "INFO: After rendering EntityGroup" << std::endl;

      //render menu
      pop_menu->render(cameraoffset_x, cameraoffset_y, zoom);

      //render Temp text
      //message->render(cameraoffset_x, cameraoffset_y, zoom);

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
  delete spritegroup_main;
  delete TextHandler;
  delete Units;
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  IMG_Quit();
  SDL_Quit();
  
  return 0;
    }
