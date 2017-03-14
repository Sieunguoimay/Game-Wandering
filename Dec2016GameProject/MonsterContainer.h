#ifndef MONSTER_CONTAINER_H
#define MONSTER_CONTAINER_H
#include"Monster.h"
#include"SoundContainer.h"
class MonsterContainer{
public:
	MonsterContainer(b2World * world,Mover*mover,
		 std::vector<Texture*>*textureCollection,
 		SoundContainer*soundCollection);
	~MonsterContainer();
	void display(const Camera&camera);
	void addNew(float x, float y);
private:
	void explode(float x,float y);
	LinkedList<Monster*>monsters;
	LinkedList<Explosion*>explosions;
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
	b2World*world;
	Mover*mover;
};


#endif //MONSTER_CONTAINER_H
