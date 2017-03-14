#include"MonsterContainer.h"

MonsterContainer::MonsterContainer(b2World * world,Mover*mover,
	 std::vector<Texture*>*textureCollection,SoundContainer*soundCollection)
	:world(world),mover(mover),
	textureCollection(textureCollection),
	soundCollection(soundCollection)
{
	
}
MonsterContainer::~MonsterContainer(){
	
	for (Node<Monster*>*iter = monsters.getFirstNode(); 
	iter != monsters.tail; iter = iter->next) {
		delete iter->data;
		iter->data = NULL;
		iter = monsters.delNode(iter);
	}
	for (Node<Explosion*>*iter = explosions.getFirstNode(); iter != explosions.tail; iter = iter->next) {
		delete iter->data;
		iter->data = NULL;
		iter = explosions.delNode(iter);
	}
	textureCollection = NULL;
	soundCollection = NULL;
	mover = NULL;
	world = NULL;
}
void MonsterContainer::display(const Camera&camera){
	for(Node<Monster*>*iter = monsters.getFirstNode();
	 iter != monsters.tail; iter = iter->next)
	{
		iter->data->seek(mover);
		iter->data->display(camera);
		if(iter->data->isDead()){
			if(!iter->data->isOutOfScreen())
				explode(iter->data->getPosition().x,iter->data->getPosition().y);
	
			delete iter->data;
			iter->data = NULL;
			iter = monsters.delNode(iter);
		}
	}
	
	for (Node<Explosion*>*iter = explosions.getFirstNode(); iter != explosions.tail; iter = iter->next) {
		iter->data->display(camera);
		if (iter->data->isDead()) {
			delete iter->data;
			iter->data = NULL;
			iter = explosions.delNode(iter);
		}
	}

}
void MonsterContainer::addNew(float x, float y){
	for(Node<Monster*>*iter = monsters.getFirstNode();
	 iter != monsters.tail; iter = iter->next)
		if(iter->data->ID==x)
			return;
	monsters.addFirst(new Monster(x,y - 80.0f,world,
		textureCollection->at(2),soundCollection->at(9),x));
}

void MonsterContainer::explode(float x,float y){
	Explosion*newExplosion = new Explosion();
	newExplosion->setup(new Vector2D(x,y),//copy it to new data location 
		textureCollection->at(3), soundCollection->at(0));//remember the order of each element =(
	explosions.addFirst(newExplosion);
	
}
