#pragma once
#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "ParticleSystem.h"
class Lightning :
	public ParticleSystem
{
public:
	Lightning(float x,float y,float velX, float velY,float size,
		Texture*texture,b2World*world,float maxSpeed = 10.0f,float maxForce = 2.0f);
	~Lightning();
	void destroyBody();
	void display(const Camera&camera);
	void seek(Vector2D*target);
protected:
	b2Body*body;
	float maxSpeed;
	float maxForce;
	bool hasDestroyedBody;
	b2World*world;
	ObjectData*objectData;
};

#endif // !LIGHTNING_H
