#ifndef SCHOOL_OF_FISH__H
#define SCHOOL_OF_FISH__H
#include"Fish.h"
class SchoolOfFish{
public:
	SchoolOfFish(Rectangle pool,b2World*world,Texture*texture,bool noFish = false);
	~SchoolOfFish();
	void display(const Camera&camera);
	void addTarget(Vector2D position);
private:
	bool inside(float x, float y);
	LinkedList<Boid*>fishes;
	Rectangle pool;
};
#endif//SCHOOL_OF_FISH__H
