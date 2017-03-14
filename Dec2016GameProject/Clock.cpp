#include "Clock.h"





Clock::Clock(float fps)
	:fps(fps)
{
}

Clock::~Clock()
{
	timeStart = 0;
	fps = 0;
}

void Clock::work()
{
	if ((Uint32)(1000 / fps) > (SDL_GetTicks() - timeStart))
		SDL_Delay((Uint32)(1000 / fps) - (SDL_GetTicks() - timeStart));
	
	timeStart = SDL_GetTicks();
}
