#include "LaserContainer.h"




LaserContainer::LaserContainer(b2World * world,std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:world(world),textureCollection(textureCollection)
	,sound(soundCollection->at(2))
{
}

LaserContainer::~LaserContainer()
{
	for (Node<Laser*>*iter = lasers.getFirstNode(); iter != lasers.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}

	for (Node<Photon*>*iter = photonContainer.getFirstNode(); iter != photonContainer.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	sound = NULL;
	textureCollection = NULL;
	world = NULL;
}

void LaserContainer::display(const Camera & camera)
{
	for (Node<Laser*>*iter = lasers.getFirstNode(); iter != lasers.tail; iter = iter->next) {
		iter->data->display(camera);
		if (iter->data->done())
		{
			delete iter->data;
			iter->data = NULL;
			iter = lasers.delNode(iter);
		}
		
	}

	for (Node<Photon*>*iter = photonContainer.getFirstNode(); iter != photonContainer.tail; iter = iter->next)
	{
		if (iter->data->position.x > camera.getPosition().x + WINDOWSIZE_W*1.5f
			|| iter->data->position.x < camera.getPosition().x - WINDOWSIZE_W*0.5f)
			iter->data->collapse();
		if (iter->data->position.y > WINDOWSIZE_H*1.5f
			|| iter->data->position.y < -WINDOWSIZE_H*2.0f)
			iter->data->collapse();

		iter->data->display(camera);
		if (iter->data->isDead())
		{
			delete iter->data;
			iter->data = NULL;
			iter = photonContainer.delNode(iter);
		}
	}
}

void LaserContainer::addNew(float x, float y)
{
	for(Node<Laser*>*iter = lasers.getFirstNode();iter !=lasers.tail;iter = iter->next)
		if(iter->data->position.x == x&&iter->data->position.y == y)
			return;

	Laser *newLaser = new Laser(world, textureCollection->at(3),
		 textureCollection->at(10),sound,&photonContainer);
	newLaser->setup(x, y, 2);
	newLaser->start();
	lasers.addFirst(newLaser);

}
