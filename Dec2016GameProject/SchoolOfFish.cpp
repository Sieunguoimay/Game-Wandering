#include"SchoolOfFish.h"
SchoolOfFish::SchoolOfFish(Rectangle pool,b2World*world,Texture*texture,bool noFish)
	:pool(pool)
{
	if(!noFish){	
		int randomFishPopulation = rand() % (int)(4 + pool.w / 100) + 2;
		for (int i = 0; i < randomFishPopulation; i++) 
			fishes.addFirst(new Fish(
				pool.x+pool.w*0.5f+rand()%10,
				pool.y+pool.h*0.5f+rand()%10,world,texture));
	}
}
SchoolOfFish::~SchoolOfFish(){
	for (Node<Boid*>*iter = fishes.getFirstNode();
		iter != fishes.tail; iter = iter->next) {
			delete ((Fish*)iter->data);
			iter->data = NULL;		
	}
}
void SchoolOfFish::display(const Camera&camera){
	for (Node<Boid*>*iter = fishes.getFirstNode(); iter != fishes.tail; iter = iter->next) {
		iter->data->applyForce(
				((Fish*)iter->data)->stayWithinPool(
				pool.x + 50, pool.y +50,
				pool.w - 100, pool.h - 100));
	
		if(inside(iter->data->getPosition().x,iter->data->getPosition().y)){
			iter->data->applyForce(((Fish*)iter->data)->flock(fishes));
			iter->data->applyForce(iter->data->pursuePrey());
			
		}else ((Fish*)iter->data)->inverse();
		
		iter->data->display(camera);
	}
}
void SchoolOfFish::addTarget(Vector2D position){
	for (Node<Boid*>*iter = fishes.getFirstNode(); iter != fishes.tail; iter = iter->next)
		iter->data->addPreyTarget(position);

}

bool SchoolOfFish::inside(float x, float y){
	if(x<pool.x)
		return false;
	if(x>pool.x+pool.w)
		return false;
	if(y>pool.y+pool.h)
		return false;
	return true;
}
