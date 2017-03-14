#pragma once
#ifndef POSTER_H
#define POSTER_H
#include"globalheader.h"
#include"Texture.h"
#include"Camera.h"
#include"SoundContainer.h"
#include"TouchManager.h"
class Poster
{
public:
	Poster(Size*wondowSize,
		Texture*texture,Texture*texturePressAnyKey, SoundContainer*soundCollection);
	~Poster();
	void handleEvent(TouchManager*touchManager);
	void display();
	void up();
	bool hasDone();
private:
	SoundContainer*soundCollection;
	Size*windowSize;
	Texture*texture;
	Texture*texturePressAnyKey;

	Vector2D position;
	float oscilationY;
	float angle;
	bool keyPressed;
	bool done;
	float velY;
};

#endif // !POSTER_H
