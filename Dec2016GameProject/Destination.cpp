#include "Destination.h"



Destination::Destination(b2World*world, void*pointer,std::vector<Texture*>*textureCollection)
	:world(world),textureCollection(textureCollection)
{
	data = new ObjectData(SomeDefine::DESTINATION_ID, pointer);
}


Destination::~Destination()
{
	for (Node<DestinationBody*>*iter = destination.getFirstNode(); iter != destination.tail; iter = iter->next) {
		delete iter->data;
	}
	textureCollection = NULL;
}
void Destination::display(const Camera & camera)
{
	for (Node<DestinationBody*>*iter = destination.getFirstNode(); iter != destination.tail; iter = iter->next) {
		iter->data->display(camera);
	}
}
void Destination::addNew(float x, float y,bool leftOrRight)
{
	DestinationBody*newDestinationBody = new DestinationBody(x,y,world, 
	textureCollection->at(19));
	newDestinationBody->setUserData(data);
	if(leftOrRight)
		destination.addFirst(newDestinationBody);
	else 
		destination.addLast(newDestinationBody);
	
}
void Destination::del(bool leftOrRight){

	if (leftOrRight) {
		delete destination.getFirstNode()->data;
		destination.getFirstNode()->data = NULL;
		destination.delFist();//right
	}
	else {
		delete destination.tail->prev->data;
		destination.tail->prev->data = NULL;
		destination.delLast();//left	
	}
}
///////////////////////////////////////////////
///////////////////////////////////////////////
DestinationBody::DestinationBody(float x,float y,b2World * world, Texture * texture)
	:world(world),texture(texture)
{
	size.w = 100;
	size.h = (size.w / texture->getSize()->w)*texture->getSize()->h;
	y -= size.h*0.5f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.gravityScale = 0;
	bd.position.Set(x*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(size.w*0.25f * UtilityFunctions::P2M(), size.h*0.25f * UtilityFunctions::P2M());

	b2FixtureDef fd;
	fd.shape = &ps;
	fd.isSensor = true;
	body->CreateFixture(&fd);
}

DestinationBody::~DestinationBody()
{
	world->DestroyBody(body);
	body = NULL;
	texture = NULL;
	world = NULL;
}


void DestinationBody::display(const Camera & camera)
{
	b2Vec2 pos = UtilityFunctions::M2P()*body->GetPosition();
	texture->render(camera, pos.x - size.w*0.5f - camera.getPosition().x, pos.y - size.h*0.5f - camera.getPosition().y, size.w, size.h);
}

void DestinationBody::setUserData(void * pointer)
{
	body->SetUserData(pointer);
}
