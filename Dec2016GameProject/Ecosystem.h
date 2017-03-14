#pragma once
#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H
#include"Camera.h"
#include"Map.h"
#include"SoundContainer.h"
#include"Texture.h"
#include"Ground.h"
#include"MonsterContainer.h"
#include"CloudContainer.h"
#include"PoleContainer.h"
#include"BridgeContainer.h"
#include"PoolContainer.h"
#include"GearContainer.h"
#include"LaserContainer.h"
#include"ReflectorContainer.h"
#include"Destination.h"
#include"LevelManager.h"
#include"Bush.h"
class Ecosystem{
public:
	Ecosystem(b2World*world,Mover*mover,Map*map,
		LevelManager*levelManager,
		std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~Ecosystem();
	void display(const Camera&camera);
	void display2(const Camera&camera);
private:
	void updateLandscape(float cameraPosX);
	void putEverything(float x, float y, char ID, bool leftOrRight);
	void delEverything(char ID,bool leftOrRight);
	void putEverythingAtFirst();
	bool conditionToPutBush(char&ID);
	Ground ground;
	MonsterContainer monsters;
	CloudContainer clouds;
	PoleContainer poles;
	BridgeContainer bridges;
	PoolContainer pools;
	GearContainer gears;
	LaserContainer emitters;
	ReflectorContainer reflectors;
	Destination destinations;
	Bushes bushes;
	//game assests
	Map*map;
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
};
#endif //ECOSYSTEM_H
