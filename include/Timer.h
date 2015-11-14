#ifndef TIMER_H_
#define TIMER_H_


#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"


class Timer
{
public:
	Timer();
	virtual ~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	Uint32 mStartTicks;		//Time at start.
	Uint32 mPausedTicks;	//Time at pause.

	bool mPaused;
	bool mStarted;
};


#endif /* TIMER_H_ */
