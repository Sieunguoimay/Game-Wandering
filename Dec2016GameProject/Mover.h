#pragma once

#ifndef MOVER_H
#define MOVER_H


#include"Skin.h"
#include"Camera.h"
#include"BunnyEar.h"
#include"Explosion.h"
#include"SoundContainer.h"
//mover is so crazy class - too complex
//let's do a revolution now
//to make it better

//as the mover die
// - create a explosion to put into the container
// - there is a pointer from camera to the position => there for the position must be reset as the explosion finish
// - but the position is for displaying skin  => it not dead then display();
// - after the explosion finish create new 
class Mover
{
public:
	friend class Controller;
	Mover(b2World*world,std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~Mover();
	void reset();
	void handleEvent(SDL_Event&mainEvent);
	void display(Camera&camera);//pass renderer in when we need
	
	void die();
	void setTarget(Vector2D position);
	float getRadarRadius()const;
	const bool& hasExploded()const;
	Vector2D*getPosition();
	void setOnGround(bool state);
private:
	void createBody();
	//what the fuck is going on with the jump function???
	//how can i adjust this bug??
	void update();
	void walk(bool state);//wall is complexer , hence make it a individual function like that
	//some things never be reset
	
	LinkedList<Explosion*>explosion;
	Skin*skin;
	BunnyEar*bunnyEar;
	b2Body*body;
	ObjectData*data;
	
	
	b2World*world;
	SoundContainer*soundCollection;
	std::vector<Texture*>*textureCollection;
	
	Size size;//size inside skin points to this 
	Vector2D*staticPosition;//float - float
	b2Vec2*jumpForce;//jump force for jump() ofcourse
	Vector2D*desiredVel;//desired velocity is for walk()
	
	
	float radius;
	float maxSpeed;
	float mass;
	float friction;//friction for stoping
	bool dead;
	bool exploded;
	bool jumpPressed;
	//control
	int minJumpDuration;
	bool walkRightPressed;
	bool walkLeftPressed;
	bool firePressed;
	int onGroundCounter;
};

#endif // !MOVER_H
