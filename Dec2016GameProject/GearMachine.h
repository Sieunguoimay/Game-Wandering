#pragma once
#ifndef GEAR_MACHINE_H
#define GEAR_MACHINE_H
#include"Gear.h"
class GearMachine{
public:
	GearMachine(float x,float y,int numberGear,
		b2World*world,std::vector<Texture*>*textureCollection);
	~GearMachine();
	void display(const Camera&camera);
	Vector2D getPosition();
	bool dead;
	
private:
	void addNew();
	LinkedList<Gear*>gears;
	Vector2D position;

	float radius;
	int numberGear;
	float speedRate;
	
	b2World*world;
	b2Body*root;
	std::vector<Texture*>*textureCollection;
};
#endif//GEAR_MACHINE

