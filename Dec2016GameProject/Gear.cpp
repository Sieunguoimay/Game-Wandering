#include"Gear.h"

Gear::Gear(float x,float y,float radius,b2World*world,Texture*texture1,Texture*texture2)
:world(world),radius(radius),texture1(texture1),texture2(texture2)
{
	position1.set(x,y);
	position2.set(x,y-radius*4);
	data = new ObjectData(SomeDefine::GEARKILLER_ID,NULL);
	createBody();
}
Gear::~Gear(){
	world->DestroyBody(body1);
	world->DestroyBody(body2);
	body1 = NULL;
	body2 = NULL;
	texture1 = NULL;
	texture2 = NULL;
	delete data;
	data = NULL;
	world = NULL;
	radius = 0.0f;
}
void Gear::display(const Camera&camera){
	
	b2Vec2 pos = body1->GetPosition();
	float angle = body1->GetAngle();
	
	texture1->render(camera,
		pos.x*UtilityFunctions::M2P() - camera.getPosition().x - radius*0.125f,
		pos.y*UtilityFunctions::M2P() - camera.getPosition().y - radius*2.0f,
		radius*0.25f, radius*4.0f, 0, angle, false);
	
	pos = body2->GetPosition();
	angle = body2->GetAngle();
	texture2->render(camera,
		pos.x*UtilityFunctions::M2P() - camera.getPosition().x - radius,
		pos.y*UtilityFunctions::M2P() - camera.getPosition().y - radius,
		2.0f*radius, 2.0f*radius, 0, angle, false);

}
void Gear::connect(b2Body*root,float motorSpeed ){
	b2RevoluteJointDef rjd;
	rjd.Initialize(root, body1, b2Vec2(position1.x*UtilityFunctions::P2M(),
				 position1.y*UtilityFunctions::P2M()));
	rjd.enableMotor = true;
	rjd.maxMotorTorque = 200;//N-m
	rjd.motorSpeed = motorSpeed;
	rjd.collideConnected = false;
	world->CreateJoint(&rjd);
}



void Gear::createBody(){
	
	
	b2BodyDef bd;
	bd.position.Set(position2.x*UtilityFunctions::P2M(),
		 position2.y*UtilityFunctions::P2M());
	//bd.userData = data;//be careful set it after create body
	bd.type = b2_dynamicBody;
	body2 = world->CreateBody(&bd);

	b2CircleShape cs;
	cs.m_radius = radius*UtilityFunctions::P2M();

	b2FixtureDef fd;
	fd.density = 0.01f;//a bit light
	fd.isSensor = true;
	fd.shape = &cs;

	body2->CreateFixture(&fd);
	body2->SetUserData(data);

	
	b2BodyDef bd2;
	bd2.position.Set(
		(position1.x)*UtilityFunctions::P2M(),
		0.5f*(position2.y + position1.y)*UtilityFunctions::P2M());
	bd2.type = b2_dynamicBody;
	body1 = world->CreateBody(&bd2);

	b2PolygonShape ps;
	ps.SetAsBox(0.125f*radius*UtilityFunctions::P2M(), 2.0f*radius*UtilityFunctions::P2M());
	
	b2FixtureDef fd2;
	fd2.shape = &ps;
	fd2.density = 1;//a bit light
	fd2.isSensor = true;

	body1->CreateFixture(&fd2);

	b2RevoluteJointDef rjd;
	rjd.Initialize(body1, body2, body2->GetWorldCenter());
	rjd.enableMotor = true;
	rjd.maxMotorTorque = 20;//N-m
	rjd.motorSpeed = 2.0f*PI;
	rjd.collideConnected = false;
	world->CreateJoint(&rjd);

}
