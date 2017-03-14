#pragma once


#ifndef GROUND_H
#define GROUND_H
#include"globalheader.h"
#include"Brick.h"
#include"Texture.h"
#include"Map.h"
#include"Camera.h"
class Ground
{
public:
	Ground(b2World*world,Texture*texture);
	~Ground();

	void display(const Camera&camera);
	
	Size getSize()const;
	
	void putNewBrick(float x, float y, int type,bool leftOrRight = false);//true is right - false is left
	
	void delBrick(bool leftOrRight = false);
private:
	
	LinkedList<Brick*>bricks;
	Size size;
	
	b2World*world;
	Texture*texture;
};

#endif // !GROUND_H
