#pragma once
#ifndef POLE_H
#define POLE_H
#include"SwarmOfBee.h"
class Pole{
public:
	Pole(float x,float y,Texture*texture);
	~Pole();
	void display(const Camera&camera);
	Vector2D getPosition();
	float getHeight();
private:
	LinkedList<SwarmOfBee*>bees;
	Vector2D position;
	Vector2D position2;
	
	Size size;
	Texture*texture;
};
#endif //POLE_H
