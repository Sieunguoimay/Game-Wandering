#ifndef POOL_H
#define POOL_H
#include"SchoolOfFish.h"
class Pool{
public:
	Pool(float x, float y, float w, float h,b2World*world,
		Texture*texture,Texture*texure2,Texture*texture3,bool hasWood = false,bool noFish = false);
	~Pool();
	void display(const Camera&camera);
	void findOut(Vector2D position);
	Rectangle area;
private:
	void createBody();
	b2Body*createWood(float x,float y);
	SchoolOfFish fishes;
	LinkedList<b2Body*>woods;
	Size size;
	ObjectData*data2;
	
	Texture*texture;
	Texture*texture3;
	b2Body*body;
	ObjectData*data;
	b2World*world;
};
#endif//POOL_H
