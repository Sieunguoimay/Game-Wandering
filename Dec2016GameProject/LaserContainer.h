#pragma once
#ifndef LASERCONTAINER_H
#define LASERCONTAINER_H

#include"Laser.h"
#include"Mover.h"
class LaserContainer
{
public:
	LaserContainer(b2World * world,std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~LaserContainer();
	void display(const Camera&camera);
	void addNew(float x, float y);

private:
	LinkedList<Laser*>lasers;
	LinkedList<Photon*>photonContainer;
	std::vector<Texture*>*textureCollection;

	Sound*sound;
	b2World*world;
};

#endif // !LASERCONTAINER_H
