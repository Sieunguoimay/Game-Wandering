#ifndef BOLT_H
#define BOLT_H
#include"globalheader.h"
#include"Sound.h"
#include"Texture.h"
#include"Camera.h"
class Bolt{
public:
	Bolt(b2World*world,Texture*texture,Texture*texturePointerToCloud,Sound*sound);
	~Bolt();
	void display(const Camera&camera);
	void calculateDischarge(Vector2D cloudPosition,Vector2D target,bool beingShown);
private:
	void drawLine(Vector2D&pos1, Vector2D & pos2, const Camera&camera);
	b2Body*addNewParticleBody(float x, float y);
	
	LinkedList<b2Body*>bodies;
	LinkedList<Vector2D*>path;
	Node<Vector2D*>*shutle;
	Texture*texturePointerToCloud;
	Texture*texture;
	b2World*world;
	ObjectData*data;
	Sound*sound;
};
#endif //BOLT_H
