#pragma once
#ifndef PHOTON_H
#define PHOTON_H
#include "Lightning.h"
class Photon :
	public ParticleSystem
{
public:
	friend class Relector;
	Photon(float x,float y,b2World*world,Texture*texture);
	~Photon();
	void setup(float x,float y);
	void collapse();
	bool hasCollapsed()const;
	void display(const Camera&camera);
private:
	bool collapsed;
	b2Body*body;
	b2World*world;
	Color*color;
	ObjectData*data;
};
#endif // !PHOTON_H
