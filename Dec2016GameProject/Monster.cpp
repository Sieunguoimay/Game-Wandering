#include"Monster.h"


int Monster::numberMonster = 0;
Monster::Monster(float x, float y,b2World*world,
		Texture*texture,
		Sound*sound,float ID)
	:world(world),texture(texture),sound(sound),ID(ID)		
{
	size.set(80.0f, 80.0f);
	position.set(x,y);
	dead = false;	
	currentSpriteIndex = 0;
	maxForce = 10.0f;
	maxSpeed = 700.0f;//0k
	createBody();
	data =  new ObjectData(SomeDefine::MONSTER_TOMATO,this);
	body->SetUserData(data);
	numberMonster++;
}
Monster::~Monster(){
	numberMonster--;
	size.set(0.0f,0.0f);
	maxForce =0.0f;
	maxSpeed = 0.0f;
	currentSpriteIndex = 0;
	position.set(0.0f,0.0f);
	dead = false;
	world->DestroyBody(body);
	body = NULL;
	delete data;
	data = NULL;
	
	texture = NULL;
	sound = NULL;	
	world = NULL;
}
void Monster::display(const Camera&camera){
	position.set(body->GetPosition().x*UtilityFunctions::M2P(),
		body->GetPosition().y*UtilityFunctions::M2P());	

	if (position.y > WINDOWSIZE_H*2.0f)
		dead = true;

	texture->render(camera,
		position.x - camera.getPosition().x - size.w/2,
		position.y - camera.getPosition().y - size.h/2,
		size.w,size.h,currentSpriteIndex,0,flip);
}
void Monster::seek(Mover*mover){
	mover->setTarget(position);
	
	float newPosX = body->GetPosition().x*UtilityFunctions::M2P();
	if ((int)(newPosX - oldPosX) != 0)
		flip = (velocity.x > 0);
	oldPosX = newPosX;


	target.set(mover->getPosition()->x,position.y);

	velocity.set(
		body->GetLinearVelocity().x*UtilityFunctions::M2P(),
		body->GetLinearVelocity().y*UtilityFunctions::M2P());
	
	desired.set(newPosX,position.y);

	desired.subtract(target);
	float distance = desired.magnitude();

	if (distance < size.w * 5) {//if the target is in a distance of 10 times its width
		desired.normalize();
		grab();
		if (distance < size.w) {//slow down as distance is smaller and smaller
			float m = UtilityFunctions::map(distance, 0, 100.0f, 0, maxSpeed);
			desired.multiply(-m);
		}
		else desired.multiply(-maxSpeed);

		desired.subtract(velocity);
		desired.limit(maxForce);
		applyForce(desired);
	}

}	
bool Monster::isDead()const{
	return dead;
}
bool Monster::isOutOfScreen(){
	if (position.y > WINDOWSIZE_H*2.0f)
		return true;
	return false;
}
void Monster::die(){
	dead = true;
}
Vector2D Monster::getPosition(){
	return position;
}
void Monster::applyForce(Vector2D force){
	body->ApplyForce(b2Vec2(force.x*UtilityFunctions::P2M(),force.y*UtilityFunctions::P2M()),
		body->GetWorldCenter(),true);
}
void Monster::grab(){
	static float timeCounter = 0.0f;
	float framePerSecond = 10;
	timeCounter += 1.0f / FPS;
	if (timeCounter >= 1 / framePerSecond) {
		currentSpriteIndex++;
		if (currentSpriteIndex >= 5) {
			currentSpriteIndex = 0;
			sound->play(10+numberMonster);
		}
		timeCounter = 0.0f;
	}
}



void Monster::createBody(){

	b2BodyDef bd;//position, type
	bd.position.Set(position.x*UtilityFunctions::P2M(), 
		position.y*UtilityFunctions::P2M());
	
	bd.type = b2_dynamicBody;
	bd.gravityScale = 3.0f;//who is heavier
	body = world->CreateBody(&bd);//each create a new body for the world

	b2CircleShape cs;
	cs.m_radius = size.w*UtilityFunctions::P2M()/2;

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.density = 0.02f;
	fd.friction = 0.05f;
	fd.restitution = 0.1f;
	
	body->CreateFixture(&fd);
}
