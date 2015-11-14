#ifndef TEXTURE_H_
#define TEXTURE_H_


#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#include "logging.h"


SDL_Texture * loadTexture(std::string file, SDL_Renderer *renderer, bool colorkey=true);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);


#endif /* TEXTURE_H_ */
