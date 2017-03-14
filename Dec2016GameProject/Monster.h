#ifndef MONSTER_H
#define MONSTER_H
#include"globalheader.h"
#include"Mover.h"
#include"Texture.h"
#include"Camera.h"
class Monster{
public:
	Monster(float x, float y,b2World*world,
		Texture*texture,
		Sound*sound,float ID);
	~Monster();
	void display(const Camera&camera);
	void seek(Mover*mover);	
	bool isDead()const;
	bool isOutOfScreen();
	void die();
	static int numberMonster;
	float ID;
	Vector2D getPosition();
private:
	void createBody();
	void applyForce(Vector2D force);
	void grab();
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	Vector2D target;
	Vector2D desired;
	
	float maxForce;
	float maxSpeed;
	
	bool dead;
	bool flip;
	float oldPosX;//for flip
	int currentSpriteIndex;
	Size size;
	
	b2Body*body;
	ObjectData*data;
	Texture*texture;
	Sound*sound;

	b2World*world;
};


#endif //MONSTER_H
