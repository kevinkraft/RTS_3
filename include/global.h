#ifndef GLOBAL_HPP_
#define GLOBAL_HPP_

#include <vector>
#include <map>

#include <SDL.h>

//Notes:
// * Everything defined in here must be const

//-------------------------------------------------------------------------------------
// Screen Constants
//-------------------------------------------------------------------------------------
const bool VSYNC_ACTIVE = true;
const bool USE_CUSTOM_CURSOR = false;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 100;
const int SPRITE_LIMIT = 1024;

//-------------------------------------------------------------------------------------
// Colours
//-------------------------------------------------------------------------------------
//THIS SHOULD BE DONE WITH SDL_Colour WHICH IS ESSANTIALLY A 4 ELEMENT VEC
const SDL_Color MENU_YELLOW = {229, 230, 0, 255};
const SDL_Color BLACK = {0, 0, 0, 255};

//-------------------------------------------------------------------------------------
// Text
//-------------------------------------------------------------------------------------
//the text height is tuned to work with this font size, changing it may result in the
//text in text boxs rendering longer than intended
const int DEFAULT_FONT_SIZE = 64;
const SDL_Colour DEFAULT_TEXT_COLOUR = BLACK;
const int ACTUAL_TEXT_HEIGHT = 35;

//-------------------------------------------------------------------------------------
// Menu Constants
//-------------------------------------------------------------------------------------
const float POP_MENU_ITEM_WIDTH = 110.;
const float POP_MENU_ITEM_HEIGHT = 35.;

//-------------------------------------------------------------------------------------
// Unit Constants
//-------------------------------------------------------------------------------------
const float UNIT_HP = 100.;
const float UNIT_INV_CAP = 10.;
const double UNIT_SPEED = 0.005;
//const double UNIT_SPEED = 0.05; //for testing
const double UNIT_EXCHANGE_SPEED = 0.01;
//const double UNIT_EXCHANGE_SPEED = 0.07; //for testing
const double UNIT_INTERACTION_RANGE = 0.3;
const double UNIT_ATTACK_DAMAGE = .01;
//const double UNIT_ATTACK_DAMAGE = .07; // for testing
const double UNIT_HUNGER_INCREASE = 0.007;
//const double UNIT_HUNGER_INCREASE = 0.0; // for testing
const double UNIT_HUNGER_DAMAGE = 0.01;
//const double UNIT_HUNGER_DAMAGE = 0.10; //for testing
const double UNIT_MAX_HUNGER = 100.;
const float UNIT_CLICK_WIDTH = 20; //in screen coords
const float UNIT_CLICK_HEIGHT = 25; //in screen coords
//Due to the sprite images being the same size as the map tile images we need to apply a correction
const float UNIT_CLICK_OFFSET_X = 0.;//10;
const float UNIT_CLICK_OFFSET_Y = 50.;//105;
//const float UNIT_WORK_SPEED = 0.01;
const float UNIT_WORK_SPEED = 0.10; //for testing

//-------------------------------------------------------------------------------------
// Item Constants
//-------------------------------------------------------------------------------------
const float FOOD_HUNGER_VALUE = -30; // 1 food = -30 hunger

//-------------------------------------------------------------------------------------
// Resource Constants
//-------------------------------------------------------------------------------------
const float DEFAULT_FOOD_RESOURCE_AMOUNT = 100.;
const float DEFAULT_WOOD_RESOURCE_AMOUNT = 20.;
//const float DEFAULT_WOOD_RESOURCE_AMOUNT = 11.; //for testing
const float RES_CLICK_WIDTH = 60;
const float RES_CLICK_HEIGHT = 65;
const float RES_CLICK_OFFSET_X = 0.;
const float RES_CLICK_OFFSET_Y = 23.;

//-------------------------------------------------------------------------------------
// Building Constants
//-------------------------------------------------------------------------------------
const float BUILDING_CLICK_WIDTH = 60;
const float BUILDING_CLICK_HEIGHT = 65;
const float BUILDING_CLICK_OFFSET_X = 0.;
const float BUILDING_CLICK_OFFSET_Y = 23.;
const float CONSTRUCTION_DEFAULT_HP = 30.;
const std::map<int,float> HUT_CONSTRUCTION_MATERIALS = {{2,100}};  //ten wood
const std::map<int,float> STOCKPILE_CONSTRUCTION_MATERIALS = {{2,200}};  //ten wood

//-------------------------------------------------------------------------------------
// Map Constants
//-------------------------------------------------------------------------------------
const int MAP_SIZE = 15; //gives the tile size of the map segments in the regions
/*const std::vector<std::vector<int>> GAME_MAP = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						{1, 1, 1, 2, 2, 2, 2, 2, 2, 1},
						{1, 1, 1, 2, 2, 2, 2, 2, 2, 1},
						{1, 0, 1, 1, 0, 2, 2, 2, 2, 1},
						{1, 0, 0, 1, 1, 2, 2, 0, 0, 1},
						{1, 0, 0, 1, 1, 1, 2, 0, 0, 1},
						{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
						{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};*/

#endif
