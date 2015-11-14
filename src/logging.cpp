#include "logging.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
