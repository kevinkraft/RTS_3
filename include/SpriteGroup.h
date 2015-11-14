#ifndef SPRITEGROUP_H_
#define SPRITEGROUP_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


#include "global.h"
#include "Sprite.h"


class SpriteGroup
{
public:
       	SpriteGroup(SDL_Renderer *renderer, bool zOrder=true);
	virtual ~SpriteGroup();

	void render(int cameraoffset_x, int cameraoffset_y, float zoom=1.0);
	void addSprite(Sprite *sprite);
	void removeSprite(Sprite *sprite);
	void sortByZOrder();

	std::vector<Sprite*> sprites;

private:
	SDL_Renderer *mRenderer;
	bool useZOrdering;
};


bool compareZOrder(Sprite *s1, Sprite *s2);


#endif
