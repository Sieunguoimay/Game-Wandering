#ifndef POLECONTAINER_H
#define POLECONTAINER_H
#include"Pole.h"
#include"SwarmOfBee.h"
class PoleContainer{
public:
	PoleContainer(b2World*world,Mover*mover,std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~PoleContainer();
	void display(const Camera&camera);
	void addNew(float x, float y,bool leftOrRight);
	void del(bool leftOrRight);
private:
	LinkedList<Pole*>poles;
	LinkedList<SwarmOfBee*>bees;
	SoundContainer*soundCollection;
	std::vector<Texture*>*textureCollection;
	b2World*world;
	Mover*mover;
};
#endif //POLECONTAINER_H

