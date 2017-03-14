#pragma once
#ifndef LASER_H
#define LASER_H
#include"Photon.h"
#include"Sound.h"
class Laser
{
public:
	Laser(b2World*world, Texture*texture, Texture*texture2, Sound*sound,
		LinkedList<Photon*>*photonContainer);
	~Laser();
	void setup(float x, float y,int direction);
	void display(const Camera&camera);

	void start();
	void cease();
	Vector2D position;
	bool done()const{
		return outOfScreen;
	}
private:
	void emit();
	float duration;
	LinkedList<Photon*>*photonContainer;
	Vector2D velocity;

	bool switcher;
	int emitCouter;
	float time;
	float size;
	bool beingShown;
	bool outOfScreen;

	Texture*texture;
	Texture*texture2;
	Sound*sound;
	
	b2World*world;
	b2Body*body;
	ObjectData*data;
};

#endif // !LASER_H
