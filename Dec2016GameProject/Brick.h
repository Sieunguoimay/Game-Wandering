#pragma once
#ifndef BRICK_H
#define BRICK_H
#include"globalheader.h"
#include"Camera.h"
#include"Texture.h"
class Brick
{
public:
	Brick(float x, float y,float w, float h,int typeBrick,b2World*world,Texture*texture);
	~Brick();
	void display(const Camera&camera);
private:
	void createBodyBrick(float x, float  y, float w, float h,bool isSensor);
	int typeBrick;
	Size size;
	
	ObjectData*data;
	b2Body*body;
	

	b2World*world;
	Texture*texture;
};
#endif//BRICK_H
