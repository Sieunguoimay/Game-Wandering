#ifndef POOL_CONTAINER_H
#define POOL_CONTAINER_H
#include"Pool.h"
class PoolContainer{
public:
	PoolContainer(b2World*world,std::vector<Texture*>*textureCollection);
	~PoolContainer();
	void display(const Camera&camera);
	void addNew(float x,float y,float size,int type);
private:
	LinkedList<Vector2D*>marks;
	LinkedList<Pool*>pools;
	b2World*world;
	std::vector<Texture*>*textureCollection;
};
#endif//POOL_CONTAINER_H
