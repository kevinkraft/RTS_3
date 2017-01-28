#include "logging.h"
#include "SDL.h"
#include "SDL_image.h"


void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
