#include"Bee.h"

Bee::Bee(float x,float y,float radar,b2World*world,Texture*texture, Sound*pursueSound)
:Boid(x,y,radar,world,texture),pursueSound(pursueSound)
{
	
	maxForce = 1.0f;
	maxSpeed = 20.0f;
	size.set(20.0f,texture->getSize()->h*20.0f/ texture->getSize()->w);
	dead = false;
	pursuePreyForce = 20.0f; 
	createBody();
	data = new ObjectData(SomeDefine::BIRD_ID,this);
	body->SetUserData(data);

}
Bee::~Bee(){
	for(Node<Vector2D*>*iter = preyTarget.getFirstNode(); iter!= preyTarget.tail; iter=  iter->next)
	{
		delete iter->data;
		iter->data = NULL;

	}
	pursueSound = NULL;
}
Vector2D Bee::followPath(Path&path){
	Vector2D target(0,0);
	static Vector2D predictPosition(0,0);
	static Vector2D shiftDistance(0,0);
	static Vector2D normalPoint(0,0);
	static float distance = 0;
	const float STEP_AHEAD = 25.0f;

	//step 1: find predicted position
	predictPosition.set(velocity);
	predictPosition.normalize();
	predictPosition.multiply(STEP_AHEAD);
	predictPosition.add(position);
	//step 2: find the normal point - projection of predicted position on the current path
	float minDistance = 10000.0f;//let it be a very large value - easy to be beaten by any value
	for (Node<Vector2D*>*iter = path.paths.getFirstNode(); iter != path.paths.tail->prev; iter = iter->next){
		const Vector2D &vertice1 =iter->data;
		const Vector2D &vertice2 = iter->next->data;
		Vector2D tempNormalPoint = getNormalPoint(predictPosition, vertice1, vertice2);
		if (tempNormalPoint.x >UtilityFunctions::max(vertice2.x, vertice1.x)
			|| tempNormalPoint.x < UtilityFunctions::min(vertice2.x, vertice1.x))
			tempNormalPoint.set(vertice2);
		float distance = Vector2D::distance(tempNormalPoint, predictPosition);
		if (minDistance > distance) {
			minDistance = distance;
			normalPoint = tempNormalPoint;//pass address only
			shiftDistance = Vector2D::subtract(vertice2, vertice1);//dynamic
		}
	}
		//step 3: find the target by moving the normal point along the direction of the path
	shiftDistance.normalize();
	shiftDistance.multiply(1.5f*STEP_AHEAD);

	target = Vector2D::add(normalPoint, shiftDistance);//dynamic
	//step 4: if the predicted position is off the path, seek that target to stay on the path
	distance = Vector2D::distance(predictPosition, normalPoint);
	if (distance > path.radius)
		return seek(target);
	return Vector2D();
}
float Bee::radar(Vector2D&moverPosition){
	float distanceSqr = Vector2D::distanceSqr(moverPosition, position);
	if (preyTarget.isEmpty()) {
		if (stayThere()) {//so i swear that this stay there function should be placed there "---*---" in fish class 
			if (distanceSqr < radarRadius*radarRadius) {//fall into the radar's area
				preyTarget.addFirst(new Vector2D(moverPosition));
			}
		}
	}
	return distanceSqr;
}

void Bee::die(){
	dead = true;
}
bool Bee::isDead()const{
	return dead;
}

Vector2D Bee::getNormalPoint(const Vector2D & predicLocation, const Vector2D & vertice1, const Vector2D & vertice2)
{
	// TODO: insert return statement here
	Vector2D a = Vector2D::subtract(predicLocation, vertice1);
	Vector2D b = Vector2D::subtract(vertice2, vertice1);

	b.normalize();
	b.multiply(Vector2D::scalarMultiply(a, b));
	b.add(vertice1.x, vertice1.y);
	return b;
}
Vector2D Bee::pursuePrey(){
	if(!preyTarget.isEmpty())
		if (!pursueSoundPlayed) {
			pursueSound->play();
			pursueSoundPlayed = true;
		}
	return Boid::pursuePrey();
}
