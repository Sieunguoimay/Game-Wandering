#ifndef CLOUD_H
#define CLOUD_H
#include"globalheader.h"
#include"Camera.h"
#include"Texture.h"
#include"SoundContainer.h"
#include"Bolt.h"
class Cloud{
public:
	Cloud(float x,float y,Texture*texture);
	~Cloud();
	void display(const Camera&camera);

	void blow(LinkedList<Cloud*>&others);

	void stayWithinValleyArea(float x, float y, float w, float h);

protected:
	void applyForce(Vector2D force);
	Vector2D align(LinkedList<Cloud*>&flock);
	Vector2D cohesion(LinkedList<Cloud*>&flock);
	Vector2D separate(LinkedList<Cloud*>&flock);
	Vector2D seek(Vector2D&target); 
	
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	float maxForce;
	float maxSpeed;
	Size size;
	Texture*texture;
};

class DarkCloud:public Cloud{
public:
	DarkCloud(float x,float y,b2World*world,Texture*texture,Texture*texture2,Sound*sound);
	~DarkCloud();
	void display(const Camera&camera);
	void addNewTarget(float x,float y);
private:
	bool isInsideCloudArea(float x,float y)const;
	Bolt bolt;
	Size area;
	LinkedList<Vector2D*>targetForBolt;
};

#endif//CLOUD_H
