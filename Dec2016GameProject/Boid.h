#ifndef BOID_H
#define BOID_H

#include"globalheader.h"
#include"Camera.h"
#include"Texture.h"
class Boid{
public:
	friend class Fish;
	Boid(float x, float y,float radar,b2World*world, Texture*texture);
	~Boid();
	void display(const Camera&camera);
	void applyForce(Vector2D force);
	Vector2D seek(Vector2D&target);
	Vector2D separate(LinkedList<Boid*>&others);
	Vector2D getPosition();
	
	Vector2D pursuePrey();
	void addPreyTarget(Vector2D&target);

protected:
	bool stayThere();
	void createBody();

	LinkedList<Vector2D*>preyTarget;
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	float maxForce;
	float maxSpeed;
	float mass;
	float angle;
	float delayTimeAfterSoughtTarget;
	float radarRadius;
	float pursuePreyForce;
	Size size;
	Texture*texture;
	b2World*world;
	b2Body*body;
	ObjectData*data;
};
#endif //BOID_H
