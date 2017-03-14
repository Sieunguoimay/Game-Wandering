#ifndef CLOUDCONTAINER_H
#define CLOUDCONTAINER_H
#include"GroupOfCloud.h"
class CloudContainer{
public:
	CloudContainer(b2World*world,std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	~CloudContainer();	
	void display(const Camera&camera);
	void addNew(float x,float y);
	void addNewDark(float x,float y);
private:
	LinkedList<GroupOfCloud*>groups;
	LinkedList<Vector2D*>marks;
	
	LinkedList<GroupOfDarkCloud*>groups2;
	LinkedList<Vector2D*>marks2;
	
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
	b2World*world;
};

#endif //CLOUDCONTAINER_H
