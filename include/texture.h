#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <iostream>
#include <string>

#include "SDL.h"
//#include "SDL2_image/SDL_image.h"

#include "logging.h"


SDL_Texture * loadTexture(std::string file, SDL_Renderer *renderer, bool colorkey=true);

int getTextureHeight(SDL_Texture *texture);
int getTextureWidth(SDL_Texture *texture);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);


#endif /* TEXTURE_H_ */
