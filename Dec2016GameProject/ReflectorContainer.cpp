#include "ReflectorContainer.h"




ReflectorContainer::ReflectorContainer(b2World * world,Texture*texture)
	:world(world),texture(texture)
{
	angles[LEFT_UP] = -PI *0.25f;
	angles[LEFT_DOWN] = -PI*0.75f;
	angles[RIGHT_UP] = PI *0.25f;
	angles[RIGHT_DOWN] = -PI *1.25f;

}

ReflectorContainer::~ReflectorContainer()
{
	for (Node<Relector*>*iter = reflectors.getFirstNode(); iter != reflectors.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	texture = NULL;
	world = NULL;
}


void ReflectorContainer::display(const Camera & camera)
{
	for (Node<Relector*>*iter = reflectors.getFirstNode(); iter != reflectors.tail; iter = iter->next)
	{
		iter->data->display(camera);
	}
}

void ReflectorContainer::addNew(float x, float y, int ID,bool leftOrRight)
{
	Relector*newReflector = new Relector(world,texture);
	newReflector->setup(x, y, angles[ID - int('a')]);
	if (newReflector)
		if(leftOrRight)
			reflectors.addFirst(newReflector);
		else 
			reflectors.addLast(newReflector);
	
}
void ReflectorContainer::del(bool leftOrRight){
	
	if (leftOrRight) {
		delete reflectors.getFirstNode()->data;
		reflectors.getFirstNode()->data = NULL;
		reflectors.delFist();//right
	}
	else {
		delete reflectors.tail->prev->data;
		reflectors.tail->prev->data = NULL;
		reflectors.delLast();//left	
	}
}
