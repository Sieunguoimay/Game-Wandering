#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include"globalheader.h"
#include"Camera.h"
#include"Layer.h"
#include"Mountain.h"
class Background
{
public:
	Background();
	~Background();
	void setup(std::vector<Texture*>*textureCollection);
	void reset(int currentLevel);
	void display(const Camera&camera);
	void display2(const Camera&camera);
private:
	Layer* addMidLayer();
	std::vector<Texture*>*textureCollection;
	Mountain*mountain;
	Mountain*mountain2;
	Color colorOverlay;
	Color skyColor;
	int alpha;
	Layer*skyground;
	LinkedList<Layer*>*midlayer;
};

#endif // !BACKGROUND_H
