#ifndef BRIDGE_CONTAINER_H
#define BRIDGE_CONTAINER_H
#include"Bridge.h"
class BridgeContainer{
public:
	BridgeContainer(b2World*world,
		std::vector<Texture*>*textureCollection);
	~BridgeContainer();
	void display(const Camera&camera);
	void addNew(float x,float y);
private:
	LinkedList<Bridge*>bridges;
	LinkedList<Vector2D*>marks;
	b2World*world;
	std::vector<Texture*>*textureCollection;
};

#endif//BRIDGE_CONTAINER_H
