#pragma once
#ifndef CLOCK_H
#define CLOCK_H
#include<SDL.h>

class Clock
{
public:
	Clock(float fps = 0.0f);
	~Clock();
	void work();
private:
	float fps;
	Uint32 timeStart;
};

#endif // !CLOCK_H
