#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include"globalheader.h"
#include"Texture.h"
#include"Camera.h"
class Particle
{
public:
	Particle(float x,float y, float velX,float velY, float size,
	 Texture * texture, int lifespan = 255,int speedOfLifespan = 7);
	~Particle();
	virtual void display(const Camera&camera);
	void applyForce(Vector2D&force);
	bool isDead();
	Vector2D position;

protected:	
	virtual void update();
	void updateParticle();
	Vector2D velocity;
	Vector2D accelaration;
	
	Texture*texture;
	Size size;
	int lifespan;
	int speedOfLifespan;
	float maxSize;
};

#endif // !PARTICLE_H
