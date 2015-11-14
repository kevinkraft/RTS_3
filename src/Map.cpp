#include "Map.h"
#include "global.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include <random>
//#include <math.h>

Map::Map(SDL_Renderer* renderer, SDL_Window *window){
  mRenderer = renderer;
  mWindow = window;
  
  mWidth = MAP_SIZE;
  mHeight = MAP_SIZE;

  mGameMap = makeMap(MAP_SIZE);
  
  int i = 0;
  for (float y=0; y<mWidth; y++){
    for (float x=0; x<mHeight; x++) {
      Sprite *tile;
      if (mGameMap[x][y] == 0){
	tile = new Sprite("res/images/iso/map/0.png", x, y, renderer, window, TILE_SIZE);
	mTiles.push_back(tile);
      } else if (mGameMap[x][y] == 1){
	tile = new Sprite("res/images/iso/map/1.png", x, y, renderer, window, TILE_SIZE);
	mTiles.push_back(tile);
      } else if (mGameMap[x][y] == 2){
	Sprite *tile0 = new Sprite("res/images/iso/map/0.png", x, y, renderer, window, TILE_SIZE);
	mTiles.push_back(tile0);
	tile = new Sprite("res/images/iso/map/forest.png", x, y, renderer, window, TILE_SIZE);
	mTiles.push_back(tile);
      }
      
      Sprite *grid = new Sprite("res/images/iso/map/grid.png", x, y, renderer, window, TILE_SIZE);
      mGrid.push_back(grid);
      
      
      i++;
      
    }
  }
  
  bDrawGrid = false;
}

Map::~Map() {
  // TODO Auto-generated destructor stub
}

//-------------------------------------------------------------------------------------
// Map class functions
//-------------------------------------------------------------------------------------

std::vector<std::vector<int>> Map::makeMap(int size)
{
  //make the game map
  
  //rands
  std::default_random_engine gen(time(NULL));
  std::uniform_int_distribution<int> fullrand(0, 2);
  std::uniform_int_distribution<int> dec(0, 5);
  std::uniform_int_distribution<int> inMS(0, MAP_SIZE);
  
  std::vector<std::vector<int>> game_map;
  std::vector<int> row;
  //fill random one seed tile in MAP_SIZE
  for (int i = 0; i < MAP_SIZE; i++)
    {
      for (int j = 0; j < MAP_SIZE; j++)
      {
	if (inMS(gen) == 0)
	  {
	    row.push_back(fullrand(gen));
	  } 
	else 
	  {
	    row.push_back(0);
	  }
      }
      game_map.push_back(row) ;
      row.clear();
    }

  //fill based on proximity to seed tile
  for (int x = 0; x < MAP_SIZE; x++)
    {
      for (int y = 0; y < MAP_SIZE; y++)
	{
	  //check nearby
	  for (int xx = x-2; xx < x+2; xx++)
	    {
	      for (int yy = y-2; yy < y+2; yy++)
		{
		  if (xx < 0 || yy < 0 || xx >= MAP_SIZE || yy >= MAP_SIZE) continue;
		  if (game_map[xx][yy] != 0 && dec(gen) == 0)
		    {
		      game_map[x][y] = game_map[xx][yy];
		      break;
		    }
		}
	    }//end check neraby      
	}
    }
  //tidy water
  int nsame;
  for (int x = 0; x < MAP_SIZE; x++)
    {
      for (int y = 0; y < MAP_SIZE; y++)
	{
	  //check same nearby
	  nsame = 0;
	  for (int xx = x-1; xx < x+1; xx++)
	    {
	      for (int yy = y-1; yy < y+1; yy++)
		{
		  if ((xx >= 0 && xx < MAP_SIZE) && (yy >= 0 && yy < MAP_SIZE))
		    {
		      if (game_map[xx][yy] == 1) nsame++;
		    }
		}
	    }
	  if (nsame >= 3) game_map[x][y] = 1;
	}
    }
  
  return game_map;
}

void Map::render(int cameraoffset_x, int cameraoffset_y, float zoom){
  
  for(std::vector<Sprite*>::iterator it = mTiles.begin(); it != mTiles.end(); ++it) {
    (*it)->render(cameraoffset_x, cameraoffset_y, zoom, 0);
  }
  if (bDrawGrid) {
    for(int i = 0; i < mGrid.size(); i++) {
      mGrid[i]->render(cameraoffset_x, cameraoffset_y, zoom, 0);
    }
  }
}

//-------------------------------------------------------------------------------------
// Other map and Coordinate functions
//-------------------------------------------------------------------------------------

float getDistBetween(float x1, float y1, float x2, float y2)
{
  //return signed distance between two points
  return sqrt( pow( x2 - x1 ,2) + pow( y2 - y1 ,2) );
}

float getIsoX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  //std::cout << "Map getIsoX: INFO: scale is: " << scale << std::endl;
  float pos_x = (x + cameraoffset_x + 2.0*(y+cameraoffset_y)) / (scale*zoom) - 1.5;
  return pos_x;
}

float getIsoY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  float pos_y = (x + cameraoffset_x - 2.0*(y+cameraoffset_y)) / (scale*zoom) + 1.5;
  return pos_y;
}

float getIsoCoordinateX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  float pos_x = getIsoX(x, y, cameraoffset_x, cameraoffset_y, zoom, scale);
  return std::floor(pos_x);
}
float getIsoCoordinateY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  float pos_y = getIsoY(x, y, cameraoffset_x, cameraoffset_y, zoom, scale);
  return std::floor(pos_y);
}

float getPixelX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  float pixel_x = 0;
  pixel_x = (scale*zoom * x * 0.5) + (scale*zoom * y * 0.5) - cameraoffset_x;  
  return pixel_x;
}

float getPixelY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom, float scale){
  float pixel_y = 0;
  pixel_y = ((scale*zoom * x * 0.25) - (scale*zoom * y * 0.25)) - cameraoffset_y;
  
  return pixel_y;
}


/*
float getIsoX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pos_x = (x + cameraoffset_x + 2.0*(y+cameraoffset_y)) / (TILE_SIZE*zoom) - 1.5;
  return pos_x;
}

float getIsoY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pos_y = (x + cameraoffset_x - 2.0*(y+cameraoffset_y)) / (TILE_SIZE*zoom) + 1.5;
  return pos_y;
}

float getIsoCoordinateX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pos_x = getIsoX(x, y, cameraoffset_x, cameraoffset_y, zoom);
  return std::floor(pos_x);
}
float getIsoCoordinateY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pos_y = getIsoY(x, y, cameraoffset_x, cameraoffset_y, zoom);
  return std::floor(pos_y);
}

float getPixelX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pixel_x = 0;
  pixel_x = (TILE_SIZE*zoom * x * 0.5) + (TILE_SIZE*zoom * y * 0.5) - cameraoffset_x;  
  return pixel_x;
}

float getPixelY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom){
  float pixel_y = 0;
  pixel_y = ((TILE_SIZE*zoom * x * 0.25) - (TILE_SIZE*zoom * y * 0.25)) - cameraoffset_y;
  
  return pixel_y;
}
*/


