#pragma once
#ifndef FISH_H
#define FISH_H
#include"Boid.h"
class Fish
	:public Boid
{
public:
	Fish(float x,float y,b2World*world, Texture*texture);
	~Fish();
	Vector2D flock(LinkedList<Boid*>&flock);
	void inverse();
	Vector2D stayWithinPool(float x, float y, float w, float h);

private:
	Vector2D align(LinkedList<Boid*>&flock);
	Vector2D cohesion(LinkedList<Boid*>&flock);
	Vector2D separate(LinkedList<Boid*>&flock);

};
#endif//FIHS_H
