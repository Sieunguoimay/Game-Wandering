#pragma once
#ifndef DESTINATION_H
#define DESTINATION_H
#include"globalheader.h"
#include"Texture.h"
#include"Camera.h"
#include"LevelManager.h"
class DestinationBody 
{
public:
	DestinationBody(float x,float y,b2World*world,Texture*texture);
	~DestinationBody();
	void display(const Camera&camera);
	void setUserData(void*pointer);
private:
	Texture*texture;
	b2Body*body;
	Size size;
	b2World*world;
};
class Destination
{
public:
	Destination(b2World*world,void*pointer,std::vector<Texture*>*textureCollection);
	~Destination();
	void setup(Texture*textureDestination, Texture*textureNextLevel);
	void display(const Camera&camera);
	void addNew(float x, float y,bool leftOrRight);
	void del(bool leftOrRight);
private:
	LinkedList<DestinationBody*>destination;
	std::vector<Texture*>*textureCollection;
	b2World*world;
	ObjectData*data;
};

#endif // !DESTINATION_H
