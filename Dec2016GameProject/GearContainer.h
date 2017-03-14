#ifndef GEAR_CONTAINER_H
#define GEAR_CONTAINER_H
#include"GearMachine.h"
class GearContainer{
public:
	GearContainer(b2World*world,std::vector<Texture*>*textureCollection);
	~GearContainer();
	void display(const Camera&camera);
	void addNew(float x,float y,int number);
private:
	LinkedList<GearMachine*>gears;
	b2World*world;
	std::vector<Texture*>*textureCollection;
};
#endif//GEAR_CONTAINER_H
