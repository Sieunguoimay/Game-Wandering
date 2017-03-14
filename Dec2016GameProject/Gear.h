#pragma once
#ifndef GEAR_H
#define GEAR_H
#include"globalheader.h"
#include"Camera.h"
#include"Texture.h"
class Gear{
public:
	Gear(float x, float y, float radius,b2World*world,Texture*texture1,Texture*texture2);
	~Gear();
	void display(const Camera&camera);
	void connect(b2Body*root,float motorSpeed = PI);
	Vector2D position2;

	b2Body*body1;
	b2Body*body2;
	
	float radius;
private:
	void createBody();
	Texture*texture1;
	Texture*texture2;

	Vector2D position1;
	b2World*world;
	ObjectData*data;
};
#endif //GEAR_H
