#ifndef BRIDGE_H
#define BRIDGE_H
#include"globalheader.h"
#include"Texture.h"
#include"Camera.h"
class Bridge{
public:
	Bridge(Vector2D position1,Vector2D position2,
		b2World*world,Texture*texture,Texture*texture2);
	~Bridge();
	void display(const Camera&camera);
	bool done()const;
	float x1;
	float x2;
private:
	b2Body*createBody(float x,float y,bool wood);
	void connect2Body(b2Body*,b2Body*);
	LinkedList<b2Body*>bodies;
	Texture*texture;
	Texture*texture2;
	ObjectData*data;
	b2World*world;
	float radius;
	bool out;
};
#endif//BRIDGE_H
