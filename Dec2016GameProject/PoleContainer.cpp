#include"PoleContainer.h"

PoleContainer::PoleContainer(b2World*world,Mover*mover,
	std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:world(world),mover(mover),
	textureCollection(textureCollection),
	soundCollection(soundCollection)
{
		
}
PoleContainer::~PoleContainer(){
	for(Node<SwarmOfBee*>*iter = bees.getFirstNode();iter!=bees.tail; iter = iter->next){
		delete iter->data;
		iter->data = NULL;
	}
	for(Node<Pole*>*iter = poles.getFirstNode();iter!=poles.tail; iter = iter->next){
		delete iter->data;
		iter->data = NULL;
	}
	
	world = NULL;
	mover = NULL;
	textureCollection = NULL;
	soundCollection  = NULL;
}
void PoleContainer::display(const Camera&camera){
	for(Node<Pole*>*iter = poles.getFirstNode();iter!=poles.tail; iter = iter->next)
		iter->data->display(camera);
	for(Node<SwarmOfBee*>*iter = bees.getFirstNode();iter!=bees.tail; iter = iter->next)
	{
		iter->data->display(camera);
		if(iter->data->done()){
			delete iter->data;
			iter->data = NULL;
			iter=  bees.delNode(iter);
		}
	}
	
}
void PoleContainer::addNew(float x, float y,bool leftOrRight){
	
	Pole*newPole = new Pole(x,y,textureCollection->at(12));
	if(leftOrRight)
		poles.addFirst(newPole);
	else	
		poles.addLast(newPole);
	
	
	for(Node<SwarmOfBee*>*iter = bees.getFirstNode();iter!=bees.tail; iter = iter->next)
		if(x==iter->data->position.x)
			return;

	bees.addLast(new SwarmOfBee(x,newPole->getPosition().y,
	newPole->getHeight(),world,mover,textureCollection,soundCollection));
}
void PoleContainer::del(bool leftOrRight){
	if (leftOrRight) {
		delete poles.getFirstNode()->data;
		poles.getFirstNode()->data = NULL;
		poles.delFist();//right
	}
	else {
		delete poles.tail->prev->data;
		poles.tail->prev->data = NULL;
		poles.delLast();//left	
	}
}
