#pragma once
#ifndef SWARMOFBEE_H
#define SWARMOFBEE_H
#include"Bee.h"
#include"SoundContainer.h"
#include"Explosion.h"
#include"Mover.h"
class SwarmOfBee{
public:
	SwarmOfBee(float x,float y,float radar,b2World*world,Mover*mover,std::vector<Texture*>*textureCollection,SoundContainer*soundCollection);
	~SwarmOfBee();
	void display(const Camera&camera);
	bool done()const;
	Vector2D position;
private:
	LinkedList<Explosion*>explosion;	
	LinkedList<Boid*>bees;
	Path path;
	Mover*mover;
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
};
#endif//SWARMOFBEE_H
