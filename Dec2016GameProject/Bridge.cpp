#include"Bridge.h"

Bridge::Bridge(Vector2D position1,Vector2D position2,
	 b2World*world,Texture*texture,Texture*texture2)
:world(world),texture(texture),texture2(texture2)
{
	radius= 15.0f;
	data = new ObjectData(SomeDefine::SURFACE_BRICK_ID,NULL);
	out = false;	
	x1 = position1.x;
	x2 = position2.x;
	float distance = Vector2D::distance(position1,position2);
	int n = (int)(distance/(2.0f*radius));
	float sinY = (position2.y-position1.y)/distance;
	float cosX = (position2.x-position1.x)/distance;
	
	for(int i = 1; i<n-1; i++){
		float delta = (i + 1)*2.0f*radius;
		bodies.addFirst(createBody(position1.x+delta*cosX, position1.y+delta*sinY,true));
		if(bodies.getSize()>=2)
			connect2Body(bodies.getFirstNode()->next->data,bodies.getFirstNode()->data);
	}
	
	bodies.addFirst(createBody(position1.x, position1.y,false));
	bodies.addFirst(createBody(position2.x, position2.y,false));
	
	if (!bodies.isEmpty()) {
		connect2Body(bodies.getFirstNode()->next->data, bodies.tail->prev->data);

		connect2Body(bodies.getFirstNode()->data,
		 bodies.getFirstNode()->next->next->data);
	}
}
Bridge::~Bridge(){
	x1 = 0.0f;
	x2 = 0.0f;
	radius = 0.0f;
	out = false;
	for(Node<b2Body*>*iter= bodies.getFirstNode();iter!=bodies.tail;iter= iter->next)
	{
		world->DestroyBody(iter->data);
		iter->data = NULL;
		iter = bodies.delNode(iter);
	}
	delete data;
	data = NULL;
	world = NULL;
	texture = NULL;
	texture2 = NULL;
}
void Bridge::display(const Camera&camera){
	
	b2Vec2 pos = bodies.getFirstNode()->next->data->GetPosition();
	float angle = bodies.getFirstNode()->next->data->GetAngle();
	texture2->render(camera,
			pos.x*UtilityFunctions::M2P() - camera.getPosition().x - radius*2,
			pos.y*UtilityFunctions::M2P() - camera.getPosition().y - radius*3*(texture2->getSize()->h / texture2->getSize()->w),
			radius * 4, radius * 4*(texture2->getSize()->h/ texture2->getSize()->w),
			0, 0, false);


	pos = bodies.getFirstNode()->data->GetPosition();
	angle = bodies.getFirstNode()->data->GetAngle();
	texture2->render(camera,
			pos.x*UtilityFunctions::M2P() - camera.getPosition().x - radius*2,
			pos.y*UtilityFunctions::M2P() - camera.getPosition().y - radius*3*(texture2->getSize()->h / texture2->getSize()->w),
			radius * 4, radius * 4*(texture2->getSize()->h/ texture2->getSize()->w),
			0, 0, false);


	for (Node<b2Body*>*iter = bodies.getFirstNode()->next->next; iter != bodies.tail; iter = iter->next)
	{
		b2Vec2 pos = iter->data->GetPosition();
		float angle = iter->data->GetAngle();
		texture->render(camera,
			pos.x*UtilityFunctions::M2P() - camera.getPosition().x - radius,
			pos.y*UtilityFunctions::M2P() - camera.getPosition().y - radius,
			radius * 2, radius * 2,
			0, angle, false);

	}
	
	if(x2<camera.getPosition().x-WINDOWSIZE_W*1.5f||
		x1>camera.getPosition().x+WINDOWSIZE_W*2.5f)
		out = true;	
}
bool Bridge::done()const{
	return out;
}

b2Body*Bridge::createBody(float x,float y,bool wood){
	b2BodyDef bd;
	bd.type = wood?b2_dynamicBody:b2_staticBody;
	bd.position.Set(x*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());//no converting position
	b2Body*newBody = world->CreateBody(&bd);
	
	b2CircleShape cs;
	cs.m_radius = radius*UtilityFunctions::P2M();
	
	b2FixtureDef fd; 
	fd.shape = &cs;
	fd.density = 1;
	fd.isSensor = !wood;
	newBody->CreateFixture(&fd);
	newBody->SetUserData(data);
	return newBody;
}


void Bridge::connect2Body(b2Body * body1, b2Body * body2)
{
	
	b2RevoluteJointDef djd;
	djd.Initialize(body1, body2, body1->GetWorldCenter());
	world->CreateJoint(&djd);
}
