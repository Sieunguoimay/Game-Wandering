#pragma once
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include"globalheader.h"
#include"Particle.h"

class ParticleSystem :public Particle
{
public:
	ParticleSystem(float x,float y, float velX,float velY, float size,
		Texture * texture, int lifespan = 255,int speedOfLifespan = 7);
	~ParticleSystem();
	//setup is the same
	void display(const Camera&camera);
	virtual bool isDead();//override the base function
	void updateSize();//use for explosion only
protected:
	void update();
	void putParticle();
	LinkedList<Particle*>particles;
};

#endif // !PARTICLESYSTEM_H
//some advertages:
//--to make a tail of a rocket with just a new ParticleSystem and setup with the pointer to the rocket's position
//--to make a bomb explosion. with a collection of Particlesystem. 
