#pragma once
#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H
#include<Box2D\Box2D.h>
#include"BuoyancyController.h"
#include"Mover.h"
#include"Monster.h"
#include"GroupOfCloud.h"
#include"Bee.h"
#include"Relector.h"
#include"LevelManager.h"
class GameContactListener :
	public b2ContactListener
{
public:
	GameContactListener();
	~GameContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	void step();
private:
	BuoyancyController*buoyancyController;
	std::set<FixturePair>fixturePairs;
};

#endif // !GAMECONTACTLISTENER_H
