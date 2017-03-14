#include"Fish.h"

Fish::Fish(float x,float y,b2World*world, Texture*texture)
	:Boid(x,y,100.0f,world,texture)
{
	mass = 1.0f;

	maxSpeed = 5.0f;
	maxForce = 0.1f;
	pursuePreyForce = 5.0f;
	size.set(40.0f, texture->getSize()->h*40.0f/ texture->getSize()->w);
	data = new ObjectData(SomeDefine::FISH_ID,NULL);
	createBody();
	this->body->SetUserData(data);
	
	float anlge = ((float)(rand()%360)/180.0f)*PI;
	float speed = (float)(rand() % (int)maxSpeed + 1);
	velocity.set(cosf(angle)*speed, sinf(angle)*speed);

}
Fish::~Fish(){
	
}
void Fish::inverse(){
	velocity.multiply(-1.0f);
}
Vector2D Fish::stayWithinPool(float x, float y, float w, float h){
	float force = 2.0f*maxForce;
	bool outofWater = false;
	bool metWall = false;

	Vector2D desired;
	if (position.x < x) {
		desired.set(maxSpeed, velocity.y);
		metWall = true;
	}
	else if (position.x > x + w) {
		desired.set(-maxSpeed, velocity.y);
		metWall = true;
	}
	if (position.y < y - 40.0f) {
		desired.set(velocity.x, maxSpeed);
		metWall = true;
		outofWater = true;
	}
	else if (position.y > y + h) {
		desired.set(velocity.x, -maxSpeed);
		metWall = true;
	}
	desired.multiply(2.0f);
	if (outofWater)
	{
		desired.multiply(2.0f);
		force *= 2.0f;
	}

	if (metWall) {
		Vector2D steer = Vector2D::subtract(desired, velocity);
		steer.limit(force);
		return steer;
	}
	return Vector2D();
}


Vector2D Fish::flock(LinkedList<Boid*>&flock){
	
	Vector2D sum(0.0f,0.0f);
	Vector2D separationForce = separate(flock);
	Vector2D alignmentForce = align(flock);
	Vector2D cohesionForce = cohesion(flock);

	separationForce.multiply(1.5f);
	alignmentForce.multiply(1.0f);
	cohesionForce.multiply(1.0f);

	sum.add(separationForce);
	sum.add(alignmentForce);
	sum.add(cohesionForce);
	return sum;
}

Vector2D Fish::align(LinkedList<Boid*>& flock)
{
	float neighborDistanceSqr = 50.0f*50.0f;//visible distance of a fish
	Vector2D sum;
	int visibleFishCounter = 0;
	for (Node<Boid*>*iter = flock.getFirstNode(); iter != flock.tail; iter = iter->next) {
		float distanceSqr = Vector2D::distanceSqr(position, iter->data->getPosition());
		if (distanceSqr > 0 && distanceSqr < neighborDistanceSqr) {
			sum.add(iter->data->velocity);
			visibleFishCounter++;
		}
	}

	if (visibleFishCounter > 0) {
		sum.divide((float)visibleFishCounter);
		sum.normalize();
		sum.multiply(maxSpeed);
		Vector2D steer = Vector2D::subtract(sum, velocity);
		steer.limit(maxForce);
		return steer;//pass value to out side
	}
	else return Vector2D();//this data is used for one time
}


Vector2D Fish::cohesion(LinkedList<Boid*>& flock)
{
	Vector2D sum;
	float visibleFishCounter = 0;
	float visibleDistanceSqr = 50.0f * 50.0f;
	for (Node<Boid*>*iter = flock.getFirstNode(); iter != flock.tail; iter = iter->next) {
		float distanceSqr = Vector2D::distanceSqr(position, iter->data->getPosition());
		if (distanceSqr > 0 && distanceSqr < visibleDistanceSqr) {
			sum.add(iter->data->position);
			visibleFishCounter++;
		}
	}
	if (visibleFishCounter > 0) {
		sum.divide(visibleFishCounter);
		return seek(sum);
	}
	else
		return Vector2D();
}

Vector2D Fish::separate(LinkedList<Boid*>& flock)
{
	const int desiredSpace = 20;
	int counter = 0;
	Vector2D sum;// = new Vector2D();//create one time use many times - when will it be destroyed???
	for (Node<Boid*>*iter = flock.getFirstNode(); iter != flock.tail; iter = iter->next) {
		float distance = Vector2D::distance(position, iter->data->getPosition());
		if (distance > 0 && distance < desiredSpace) {
			Vector2D difference = Vector2D::subtract(position, iter->data->getPosition());
			difference.normalize();
			difference.divide(distance);
			sum.add(&difference);
			counter++;
		}
	}
	if (counter > 0) {
		sum.divide((float)counter);
		sum.normalize();
		sum.multiply(maxSpeed);

		Vector2D steeringForce = Vector2D::subtract(sum,velocity);
		steeringForce.limit(maxForce);
		return steeringForce;
	}
	else return Vector2D();
}

