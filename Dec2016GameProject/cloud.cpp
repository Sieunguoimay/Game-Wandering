#include"cloud.h"



Cloud::Cloud(float x,float y,Texture*texture)
	:texture(texture)
{
	maxForce = 0.02f;
	maxSpeed = 1.0f;
	position.set(x, y);
	velocity.set((float)(rand() % 10+1), (float)(rand() % 10) / 10.0f);
	size.w = (float)(100 + rand() % 50);
	size.h = texture->getSize()->h * size.w/ texture->getSize()->w;
}
Cloud::~Cloud(){
	texture = NULL;
}
void Cloud::display(const Camera&camera){
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	position.add(velocity);
	acceleration.multiply(0.0f);

	texture->render(camera,
		(position.x - size.w / 2.0f - camera.getPosition().x),
		(position.y - size.h / 2.0f - camera.getPosition().y),
		size.w, size.h, 0);

}

void Cloud::blow(LinkedList<Cloud*>&others)
{
	applyForce(separate(others));
	applyForce(align(others));
	applyForce(cohesion(others));
}


void Cloud::stayWithinValleyArea(float x, float y, float w, float h)
{

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
	if (position.y < y ) {
		desired.set(velocity.x, maxSpeed);
		metWall = true;
	}
	else if (position.y > y + h) {
		desired.set(velocity.x, -maxSpeed);
		metWall = true;
	}
	if (metWall) {
		Vector2D steer = Vector2D::subtract(desired, velocity);
		steer.limit(maxForce);
		applyForce(steer);
	}
}

Vector2D Cloud::align(LinkedList<Cloud*>& flock)
{
	float neighborDistanceSqr = 50.0f * 50.0f;//visible distance of a fish
	Vector2D sum;
	int visibleFishCounter = 0;
	for (Node<Cloud*>*iter = flock.getFirstNode(); iter != flock.tail; iter = iter->next) {
		float distanceSqr = Vector2D::distanceSqr(position, iter->data->position);
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

Vector2D Cloud::cohesion(LinkedList<Cloud*>& flock)
{
	Vector2D sum;
	float visibleFishCounter = 0.0f;
	float visibleDistanceSqr = 50.0f * 50.0f;
	for (Node<Cloud*>*iter = flock.getFirstNode(); iter != flock.tail; iter = iter->next) {
		float distanceSqr = Vector2D::distanceSqr(position, iter->data->position);
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

Vector2D Cloud::separate(LinkedList<Cloud*>& others)
{
	const int desiredSpace = (const int)(size.getHalfPerimeter()*0.5f);
	int counter = 0;
	Vector2D sum;// = new Vector2D();//create one time use many times - when will it be destroyed???
	for (Node<Cloud*>*iter = others.getFirstNode(); iter != others.tail; iter = iter->next) {
		float distance = Vector2D::distance(position, iter->data->position);
		if (distance > 0 && distance < desiredSpace) {
			Vector2D difference = Vector2D::subtract(position, iter->data->position);
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

		Vector2D steeringForce = Vector2D::subtract(sum, velocity);
		steeringForce.limit(maxForce);
		return steeringForce;
		//applyForce(steeringForce);
	}
	return Vector2D();
}

Vector2D Cloud::seek(Vector2D&target)
{
	Vector2D desired = Vector2D::subtract(target, position);
	float d = desired.magnitude();
	desired.normalize();

	//to slow down the speed of vehicle
	if (d < 100.0f) {
		float m = UtilityFunctions::map(d, 0.0f, 100.0f, 0.0f, maxSpeed);
		desired.multiply(m);
	}
	else desired.multiply(maxSpeed);

	//create steer
	Vector2D steer = Vector2D::subtract(desired, velocity);
	steer.limit(maxForce);

	return steer;

}

void Cloud::applyForce(Vector2D force)
{
	acceleration.add(force.x, force.y);
}







////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

DarkCloud::DarkCloud(float x,float y,b2World*world,Texture*texture,Texture*texture2,Sound*sound)
	:Cloud(x,y,texture),
	bolt(world,texture2,texture,sound)
{
	area.set(size.w*2.0f,WINDOWSIZE_H*0.5f);	
}
DarkCloud::~DarkCloud(){
	for(Node<Vector2D*>*iter = targetForBolt.getFirstNode();iter!=targetForBolt.tail;iter = iter->next){
		delete iter->data;
		iter->data = NULL;
		iter = targetForBolt.delNode(iter);
	}
	
}
void DarkCloud::display(const Camera&camera){
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	position.add(velocity);
	acceleration.multiply(0.0f);

	bool isInsideWindow = 
		position.x > camera.getPosition().x&&
		position.x < camera.getPosition().x + WINDOWSIZE_W;

	for (Node<Vector2D*>*iter = targetForBolt.getFirstNode(); iter != targetForBolt.tail; iter = iter->next)
	{
		bolt.calculateDischarge(position, *iter->data,isInsideWindow);

		delete iter->data;
		iter->data = NULL;
		iter = targetForBolt.delNode(iter);
	}

	if (targetForBolt.isEmpty())
		if (rand() % 10000 < 20) 
			bolt.calculateDischarge(position,Vector2D(
					position.x + ((int)(area.w*0.5f)>0 ?(rand() % (int)(area.w*0.5f)):0)
					 - area.w*0.25f,
					position.y + ((int)(area.h / 3.0f)>0?(rand() % (int)(area.h / 3.0f)):0) 
					+ area.h / 3.0f),
					isInsideWindow);
		
	


	texture->setColor(0x55, 0x55, 0x55);
	bolt.display(camera);
	texture->render(camera,
		(position.x - size.w / 2.0f - camera.getPosition().x),
		(position.y - size.h / 2.0f - camera.getPosition().y),
		size.w, size.h, 0);
	texture->setColor(0xff, 0xff, 0xff);

}
void DarkCloud::addNewTarget(float x,float y){
	
	if (isInsideCloudArea(x,y)) {
		if (targetForBolt.isEmpty())
			targetForBolt.addFirst(new Vector2D(x,y));
		else if (y < targetForBolt.getFirstNode()->data->y)
		{
			delete targetForBolt.getFirstNode()->data;
			targetForBolt.getFirstNode()->data = NULL;
			targetForBolt.emptyList();
			targetForBolt.addFirst(new Vector2D(x,y));
		}
	}
}


bool DarkCloud::isInsideCloudArea(float x,float y) const
{

	if (x < position.x-area.w*0.5f)
		return false;
	if (x > position.x+area.w*0.5f)
		return false;
	if (y < position.y)
		return false;

	return true;
}
