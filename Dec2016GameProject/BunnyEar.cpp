#include "BunnyEar.h"


BunnyEar::BunnyEar(float w, float h,b2World*world,b2Body*staticBody,
	Texture*texture,Texture*textureLightning)
	:world(world),texture(texture),textureLightning(textureLightning)
{
	position = new Vector2D();
	
	size.set(w, h);//size of the box body and be the size for rendering texture also
	radarRadius = 250.0f;
	hasSetTarget = false;
	
	setup(staticBody);
}


BunnyEar::~BunnyEar()
{
	radarRadius = 0.0f;
	world->DestroyBody(body);
	for(Node<Lightning*>*iter = lightPower.getFirstNode();iter!=lightPower.tail;iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	body = NULL;
	delete position;
	position = NULL;
	texture = NULL;
	textureLightning = NULL;
}


void BunnyEar::setup(b2Body*staticBody)
{
	
	float w = size.w*UtilityFunctions::P2M();
	float h = size.h*UtilityFunctions::P2M();

	b2Vec2 origin(
		staticBody->GetPosition().x,
		staticBody->GetPosition().y - h / 2);
	//where h is equal to radius of the staticbody
	b2Vec2 bodyPosition(origin.x, origin.y - h / 2.0f);

	//create body
	b2Vec2 vertice[4];
	vertice[0].Set(-w / 2.0f, h / 2.0f);
	vertice[1].Set(w / 2.0f, h / 2.0f);
	vertice[2].Set(w / 2.0f, -h / 2.0f);
	vertice[3].Set(-w / 2.0f, -h / 2.0f);

	b2BodyDef bd;
	bd.position.Set(bodyPosition.x, bodyPosition.y);
	bd.type = b2_dynamicBody;
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.Set(vertice, 4);

	b2FixtureDef fd;
	fd.isSensor = true;
	fd.shape = &ps;
	fd.density = 0.0001f;//very light
	body->CreateFixture(&fd);

	//connect 2 body
	b2RevoluteJointDef rjd;

	rjd.Initialize(staticBody, body, origin);
	rjd.enableLimit = true;
	rjd.lowerAngle = -3.141592f / 6.0f;
	rjd.upperAngle = 3.141592f / 6.0f;

	world->CreateJoint(&rjd);
}

void BunnyEar::display(const Camera & camera)
{
	position->set( body->GetPosition().x*UtilityFunctions::M2P(),body->GetPosition().y*UtilityFunctions::M2P());
	float angle = body->GetAngle();

	//if target is set out side then the flag is true, this step is skiped then we should set to false to serve for next loop
	if (!hasSetTarget)
		setTarget(*position);
	else hasSetTarget = false;

	
	texture->render(camera,
		position->x - size.w*0.5f - camera.getPosition().x,
		position->y- size.h*0.5f - camera.getPosition().y,
		size.w, size.h, 0, angle, false);

	for (Node<Lightning*>*iter = lightPower.getFirstNode(); iter != lightPower.tail; iter = iter->next)
	{
		iter->data->seek(&target);
		iter->data->display(camera);
		if (iter->data->isDead()) {
			delete iter->data;
			iter = lightPower.delNode(iter);
		}
	}
}

void BunnyEar::discharge()
{
	if (lightPower.getSize() < 5) {
		float angle = (float)(rand() % 360 + 1)*3.141592f / 180.0f;
		float maxSpeed = (float)(rand() % 20 + 1);
		Lightning*newParticleSystem = new Lightning(
			position->x,position->y,maxSpeed*cosf(angle), maxSpeed*sinf(angle),
			50.0f,textureLightning,
			world,20.0f,3.0f);
		lightPower.addFirst(newParticleSystem);
	}
}

void BunnyEar::setTarget(Vector2D & target)
{
	this->target.set(&target);
	this->hasSetTarget = true;
}

float BunnyEar::getRadaRadius() const
{
	return radarRadius;
}

float BunnyEar::getDistanceSqrToTarget()
{
	return Vector2D::distanceSqr(position,&target);
}

