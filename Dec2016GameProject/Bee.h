#ifndef BEE_H
#define BEE_H
#include"Boid.h"
#include"Path.h"
#include"SoundContainer.h"
class Bee:public Boid
{
public:
	Bee(float x,float y,float radar,b2World*world,Texture*texture, Sound*pursueSound);
	~Bee();
	Vector2D followPath(Path&path);
	float radar(Vector2D&moverPosition);
	void die();
	bool isDead()const;
private:
	Vector2D getNormalPoint(const Vector2D & predicLocation, const Vector2D & vertice1,
	 const Vector2D & vertice2);
	Vector2D pursuePrey();
	//Path*path;
	bool dead; 
	bool pursueSoundPlayed;
	Sound*pursueSound;

};
#endif//BEE_H
