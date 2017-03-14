#ifndef GROUP_OF_CLOUD_H
#define GROUP_OF_CLOUD_H
#include"cloud.h"
class GroupOfCloud{
public:
	GroupOfCloud(float x,float y,float w, float h,std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection);
	~GroupOfCloud();
	void display(const Camera&camera);
	Rectangle rectangle;
private:
	LinkedList<Cloud*>clouds;
};

class GroupOfDarkCloud{
public:
	GroupOfDarkCloud(float x,float y,float w, float h,
	b2World*world,
	std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection);
	
	~GroupOfDarkCloud();
	void display(const Camera&camera);
	Rectangle rectangle;
	void findOut(Vector2D position);
private:
	Vector2D newTarget;
	bool isThereNewTarget;
	LinkedList<Cloud*>clouds;
	b2Body*body;
	b2World*world;
	ObjectData*data;
};

#endif//GROUP_OF_CLOUD_H	
