#pragma once

#ifndef SKIN_H
#define SKIN_H
#include"Texture.h"
#include"globalheader.h"
#include"Camera.h"
class Skin
{
public:
	Skin(Texture*bodyTexture,Texture*legsTexture,Texture*eyeTexture,
		Size*size,Vector2D*position);
	~Skin();
	void render(const Camera&camera);
	void walk(float velocityX);
private:
	void blink();
	std::vector<int>spriteIndices;

	bool horizontalFlip;
	float secondPerLoop;
	int numLegSprites;

	int numberBodySprite;
	Size*size;
	Vector2D*position;
	
	Texture*bodyTexture;
	Texture*legsTexture;
	Texture*eyeTexture;
};

#endif // !SKIN_H
