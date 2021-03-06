#ifndef MAP_H_
#define MAP_H_


#include <string>
#include <cmath>
#include <vector>

//#include "yaml-cpp/yaml.h"
#include "SDL.h"
//#include "SDL2_image/SDL_image.h"


#include "Sprite.h"
#include "global.h"


class Map{
 public:
  Map(int xpos, int ypos, int width, int height, int seed, SDL_Renderer *renderer, SDL_Window *window);
  virtual ~Map();

  void render(int cameraoffset_x, int cameraoffset_y, float zoom=1);

  bool getDrawGrid() {return bDrawGrid;}
  void setDrawGrid(bool drawgrid) {bDrawGrid = drawgrid;}

  std::vector<Sprite*> mTiles;
  std::vector<Sprite*> mGrid;

  int mWidth;
  int mHeight;

  int mPosX;
  int mPosY;

  std::vector<std::vector<int>> mGameMap;
  std::vector<std::vector<int>> makeMap(int size);

  SDL_Renderer *mRenderer;
  SDL_Window *mWindow;

 private:
  bool bDrawGrid;
  int mSeed;

};

float getDistBetween(float x1, float y1, float x2, float y2);
bool pointInSquare(float x, float y, float sq_x, float sq_y, float sq_w, float sq_h);

float getIsoX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom=1.0, float scale=TILE_SIZE);
float getIsoY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom=1.0, float scale=TILE_SIZE);
float getIsoCoordinateX(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom=1.0, float scale=TILE_SIZE);
float getIsoCoordinateY(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom=1.0, float scale=TILE_SIZE);

float getPixelX(float x, float y, int cameraoffset_x=0, int cameraoffset_y=0, float zoom=1.0, float scale=TILE_SIZE);
float getPixelY(float x, float y, int cameraoffset_x=0, int cameraoffset_y=0, float zoom=1.0, float scale=TILE_SIZE);

#endif
