#pragma once
#ifndef YOUWIND_H
#define YOUWIND_H
#include"globalheader.h"
#include"Explosion.h"
#include"SoundContainer.h"
class FireWork;
class YouWin
{
public:
	YouWin(std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~YouWin();
	void display(const Camera&camera);
	bool done()const;
private:
	void addNewFireWork(float x, float y,float w,float h);
	LinkedList<FireWork*> fireWork;
	float timeDisplay;
	
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
};

class FireWork {
public:
	FireWork(float x, float y, Texture*texture, Texture * texture2, Sound*sound);
	~FireWork();
	void display(const Camera&camera);
	bool isDead()const;
private:
	LinkedList<Explosion*> explosion;
	Texture*texture;
	Texture*texture2;
	Sound*sound;
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	float damping;
	float size;
	bool dead;
	bool flip;
};
#endif // !YOUWIND_H
