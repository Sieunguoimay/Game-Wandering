#pragma once
#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include"MountainBrick.h"
#include"Perlin.h"
typedef LinkedList<LinkedList<MountainBrick*>*> MountainMatrix;
class Mountain
{
public:
	Mountain();
	~Mountain();
	void setup(Texture*texture, float cameraRate, Color*color);
	void display(const Camera&camera);
private:
	void updateMountain(float cameraX);

	LinkedList<MountainBrick*>*putBrickAccordingToNoise(float xOff);
	void delBrick(bool leftOrRight);
	void putBricksAtFirst();
	MountainMatrix*bricks;
	Size*size;
	Texture*texture;
	float cameraRate;
	Color*color;
	Perlin*perlinNoise;
	static float differenceNoise;
	
};

#endif // !MOUNTAIN_H
