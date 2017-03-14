#include "Particle.h"



Particle::Particle(float x,float y, float velX,float velY, float size,
	 Texture * texture, int lifespan, int speedOfLifespan)
	 :position(x,y),velocity(velX,velY),size(size,size),
	 texture(texture),lifespan(lifespan),speedOfLifespan(speedOfLifespan)
{
	maxSize = size;
}


Particle::~Particle()
{
	texture = NULL;
}

void Particle::display(const Camera & camera)
{
	update();
	updateParticle();
	texture->render(camera,
		position.x - size.w*0.5f - camera.getPosition().x,
		position.y - size.h*0.5f- camera.getPosition().y,
		size.w, size.h,0, 0, false);	
}

void Particle::applyForce(Vector2D & force)
{
	this->accelaration.set(&force);
}

bool Particle::isDead()
{
	return (lifespan <= 0);
}

void Particle::update()
{
	velocity.add(accelaration);
	position.add(velocity);
	lifespan -= speedOfLifespan;
}

void Particle::updateParticle()
{
	if (lifespan < 0)
		lifespan = 0;
	size.w = (maxSize*(float)(255 - lifespan) / 255.0f);
	size.h = (maxSize*(float)(255 - lifespan) / 255.0f);
	texture->setAlpha(lifespan);
}
