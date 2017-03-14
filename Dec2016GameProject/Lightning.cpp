#include "Lightning.h"



Lightning::Lightning(float x,float y, 
	float velX, float velY, float size, Texture * texture,
	
	b2World*world,float maxSpeed , float maxForce)
	:world(world),maxForce(maxForce),maxSpeed(maxSpeed)
	,ParticleSystem(x,y, velX,velY, size, texture, 100)

{
	this->hasDestroyedBody = false;
	
	b2BodyDef bd;
	bd.position.Set(x*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());
	bd.type = b2_kinematicBody;
	body = world->CreateBody(&bd);

	b2CircleShape cs;
	cs.m_radius = 10*UtilityFunctions::P2M();

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.isSensor = true;
	body->CreateFixture(&fd);

	objectData = new ObjectData(SomeDefine::MOVER_LIGHTNING, this);
	body->SetUserData(objectData);

}

Lightning::~Lightning()
{
	this->hasDestroyedBody = false;
}

void Lightning::destroyBody()
{
	world->DestroyBody(body);


	body = NULL;
	objectData->pointer = NULL;
	delete objectData;//object Data should be destroyed after the body is cleared-because body sill point to that data memory
	this->hasDestroyedBody = true;
	b2Vec2 a;
}

void Lightning::display(const Camera & camera)
{
	ParticleSystem::display(camera);

	if(!hasDestroyedBody)
	body->SetLinearVelocity(b2Vec2(velocity.x*0.5f, velocity.y*0.5f));//yes we have to devide by 2 ><

	if(lifespan<=0&&!hasDestroyedBody)
		destroyBody();

}

void Lightning::seek(Vector2D * target)
{

	Vector2D desired = Vector2D::subtract(target, position);
	desired.normalize();
	desired.multiply(maxSpeed);

	//steering force
	desired.subtract(velocity);
	desired.limit(maxForce);
	
	//apply steering force for the body
	applyForce(desired);
}

