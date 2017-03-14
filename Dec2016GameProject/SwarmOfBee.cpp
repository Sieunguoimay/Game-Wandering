#include"SwarmOfBee.h"

SwarmOfBee::SwarmOfBee(float x,float y,float radar,b2World*world,Mover*mover,std::vector<Texture*>*textureCollection,SoundContainer*soundCollection)
	:mover(mover),
	textureCollection(textureCollection),
	soundCollection(soundCollection)
	,path(x,y)
{
	position.set(x,y);
	int randomNumOfBirdsInAFlock = rand() % 3 + 5;//3-8 birds, i think, are ok
	for (int i = 0; i < randomNumOfBirdsInAFlock; i++)
		bees.addFirst(new Bee(x,y,radar,world,
		textureCollection->at(11),soundCollection->at(12)));
}
SwarmOfBee::~SwarmOfBee(){
	for (Node<Boid*>*iter = bees.getFirstNode(); iter != bees.tail;iter = iter->next) {
		delete iter->data;
		iter->data = NULL;
	}
	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next) {
		delete iter->data;
		iter->data = NULL;
	}
	position.set(0,0);
}
void SwarmOfBee::display(const Camera&camera){
	float moverRadarRadiusSqr =
		 mover->getRadarRadius()*mover->getRadarRadius();
	for (Node<Boid*>*iter = bees.getFirstNode(); iter != bees.tail; iter = iter->next) {
		float temp = ((Bee*)iter->data)->radar(*mover->getPosition());
		if(temp<moverRadarRadiusSqr){
			moverRadarRadiusSqr = temp;
			mover->setTarget(iter->data->getPosition());
		}
		iter->data->applyForce(iter->data->separate(bees));
		iter->data->applyForce(((Bee*)iter->data)->followPath(path));
		iter->data->applyForce(iter->data->pursuePrey());
		iter->data->display(camera);
		
	
		bool outOfScreen = false;
		if (iter->data->getPosition().x > camera.getPosition().x + WINDOWSIZE_W*1.5f
			|| iter->data->getPosition().x < camera.getPosition().x - WINDOWSIZE_W*1.5f)
		{
			((Bee*)iter->data)->die();//die of falling out window
			outOfScreen = true;
		}

		if (iter->data->getPosition().y > WINDOWSIZE_H*1.5f
			|| iter->data->getPosition().y < -WINDOWSIZE_H*3.0f) {
			((Bee*)iter->data)->die();
			outOfScreen = true;
		}

		if (((Bee*)iter->data)->isDead()) {
			if (!outOfScreen) {
				//put new Explosion before being destroyed
				Explosion*newExplosion = new Explosion2();
				if (newExplosion) {
					newExplosion->setup(
						new Vector2D(iter->data->getPosition().x,
									iter->data->getPosition().y),
						textureCollection->at(3), soundCollection->at(10));
					newExplosion->color->set(0xaa,0x55,0xee);
	
					explosion.addFirst(newExplosion);
				}
			}
			delete ((Bee*)iter->data);
			iter->data = NULL;
			iter = bees.delNode(iter);
		}	
	}
	
	
	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next) {
		iter->data->display(camera);
		if (iter->data->isDead()) {
			delete iter->data;
			iter->data = NULL;
			iter = explosion.delNode(iter);
		}
	}
}


bool SwarmOfBee::done() const
{
	return (bees.isEmpty()&&explosion.isEmpty());
}
