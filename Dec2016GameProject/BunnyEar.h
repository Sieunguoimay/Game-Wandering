#pragma once
#ifndef BUNNYEAR_H
#define BUNNYEAR_H
#include"globalheader.h"
#include"Camera.h"
#include"Texture.h"
#include"Lightning.h"
class BunnyEar
{
public:
	BunnyEar(float w, float h,b2World*world,b2Body*staticBody,
	Texture*texture,Texture*textureLightning);
	~BunnyEar();
	void setup(b2Body*staticBody);
	void display(const Camera&camera);
	void discharge();
	void setTarget(Vector2D&target);
	float getRadaRadius()const;
	float getDistanceSqrToTarget();
private:
	b2Body*body;
	Size size;
	Vector2D*position;
	Texture*texture;
	Texture*textureLightning;
	b2World*world;
	LinkedList<Lightning*>lightPower;
	Vector2D target;
	bool hasSetTarget;
	float radarRadius;
};

#endif // !BUNNYEAR_H
