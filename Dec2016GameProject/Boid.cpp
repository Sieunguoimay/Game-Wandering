#include"Boid.h"
Boid::Boid(float x, float y,float radar,b2World*world, Texture*texture)
	:world(world),texture(texture),radarRadius(radar)
{
	position.set(x,y);	
	mass = 1.0f;
	delayTimeAfterSoughtTarget = 0.0f;
}
Boid::~Boid(){
	world->DestroyBody(body);
	body  = NULL;
	delete data;
	data = NULL;
	world = NULL;
	texture = NULL;
	mass = 0.0f;
	maxForce = 0.0f;
	maxSpeed = 0.0f;
	position.set(0.0f,0.0f);
	size.set(0.0f, 0.0f);
	delayTimeAfterSoughtTarget = 0.0f;
	
}
void Boid::display(const Camera&camera){
	
	velocity.add(acceleration);
	velocity.limit(maxSpeed);
	position.add(velocity);
	acceleration.multiply(0.0f);//i know why this is 0 =))
	
	if (velocity.magnitude() > 0.005f)//incase velocity is equal to 0, let angle remain
		angle = velocity.getAngle();
	
	
	body->SetLinearVelocity(b2Vec2(velocity.x *0.5f, velocity.y *0.5f));

	
	texture->render(camera,position.x - camera.getPosition().x - size.w*0.5f,
		position.y - camera.getPosition().y - size.h*0.5f,size.w,size.h,0,angle);
}
void Boid::applyForce(Vector2D force){
	acceleration.add(force.x/mass,force.y/mass);
}
Vector2D Boid::seek(Vector2D&target){
	
	Vector2D desired = Vector2D::subtract(target, position);
	float d = desired.magnitude();
	desired.normalize();

	//to slow down the speed of vehicle
	if (d < 100) {
		float m = UtilityFunctions::map(d, 0, 100, 0, maxSpeed);
		desired.multiply(m);
	}
	else
		desired.multiply(maxSpeed);

	//create steer
	Vector2D steer = Vector2D::subtract(desired, velocity);
	steer.limit(maxForce);

	return steer;
}
Vector2D Boid::separate(LinkedList<Boid*>&others){
	
	const int desiredSpace = 20;
	int counter = 0;
	Vector2D sum;// = new Vector2D();//create one time use many times - when will it be destroyed???
	for (Node<Boid*>*iter = others.getFirstNode(); iter != others.tail; iter = iter->next) {
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

		Vector2D steeringForce = Vector2D::subtract(sum,velocity);
		steeringForce.limit(maxForce);
		return steeringForce;
	}
	else return Vector2D();
}
Vector2D Boid::getPosition(){
	return position;
}
void Boid::createBody(){
	
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(position.x*UtilityFunctions::P2M(), position.y*UtilityFunctions::P2M());
	bd.gravityScale = 0;
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(0.5f*size.w* UtilityFunctions::P2M(),
				 0.5f*size.h * UtilityFunctions::P2M());

	b2FixtureDef fd;
	fd.shape = &ps;
	fd.isSensor = true;
	body->CreateFixture(&fd);
	
	
}


bool Boid::stayThere()
{
	delayTimeAfterSoughtTarget += 1.0f / FPS;
	if (delayTimeAfterSoughtTarget > 1.50f) {//1.5seconds
		delayTimeAfterSoughtTarget = 0;
		return true;
	}
	return false;
}
void Boid::addPreyTarget(Vector2D&target){
	if (preyTarget.isEmpty())
		preyTarget.addFirst(new Vector2D(&target));
}
Vector2D Boid::pursuePrey(){
	Vector2D tempForce;
	for (Node<Vector2D*>*iter = preyTarget.getFirstNode(); iter != preyTarget.tail; iter = iter->next)
	{
		float temp = maxForce;
		maxForce = pursuePreyForce;
		tempForce = seek(*iter->data);
		maxForce = temp;
		if( Vector2D::distanceSqr(*iter->data,position)<100.0f*100.0f)
		{
			delete iter->data;
			iter->data = NULL;
			iter = preyTarget.delNode(iter);
		}
	}
	return tempForce;
}

