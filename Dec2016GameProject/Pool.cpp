#include"Pool.h"

Pool::Pool(float x, float y ,float w, float h,b2World*world,
	Texture*texture,Texture*texture2,Texture*texture3,bool hasWood,bool noFish)
	:area(x,y,w,h),
	world(world),
	texture(texture),texture3(texture3)
	,fishes(area,world,texture2,noFish)
{
	data = new ObjectData(SomeDefine::WATER_POOL_ID,this);
	data2  =new ObjectData(SomeDefine::SURFACE_BRICK_ID,NULL);
	createBody();
	size.set(150.0f,150.0f/texture3->getSize()->w*texture3->getSize()->h);
	if(hasWood){		
		int n = (int)(area.w/(size.w*1.5f));
		for (int i = 0; i < n; i++) 
			woods.addFirst(createWood(area.x+size.w*1.5f*(i+1),area.y));
	}
	
}
Pool::~Pool(){
	area.set(0.0f,0.0f,0.0f,0.0f);
	size.set(0.0f,0.0f);
	world->DestroyBody(body);
	body = NULL;
	for(Node<b2Body*>*iter = woods.getFirstNode(); iter!= woods.tail; iter = iter->next)
	{
		world->DestroyBody(iter->data);
		iter->data = NULL;
	}
	delete data;
	data = NULL;
	delete data2;
	data2 = NULL;
	world = NULL;
	texture = NULL;
	texture3 = NULL;
}
void Pool::display(const Camera&camera){
	for(Node<b2Body*>*iter = woods.getFirstNode(); iter!= woods.tail; iter = iter->next)
	{
		b2Vec2 pos = iter->data->GetPosition();
		pos*=UtilityFunctions::M2P();
		float angle = iter->data->GetAngle();
		texture3->render(camera,
			pos.x - camera.getPosition().x-size.w*0.5f,
			pos.y - camera.getPosition().y-size.h*0.5f ,size.w,size.h,0,angle,false);
	}
	fishes.display(camera);
	texture->setAlpha(70);
	texture->setColor(95,125,225);
	texture->render(camera,area.x-camera.getPosition().x,
		area.y-camera.getPosition().y,area.w,area.h,0);
	texture->setColor(255,255,255);
}
void Pool::findOut(Vector2D position){
	fishes.addTarget(position);
}
void Pool::createBody(){
		b2BodyDef bd;
		bd.type = b2BodyType(0);
		bd.position.Set(area.x + area.w*0.5f, area.y + area.h*0.5f);
		bd.position *= (float32)UtilityFunctions::P2M();
		bd.allowSleep = bool(4);
		bd.awake = bool(2);
		bd.active = bool(32);
		bd.gravityScale = 1.000000000000000e+00f;
		body = world->CreateBody(&bd);

		b2FixtureDef fd;
		fd.friction = 2.000000029802322e-01f;
		fd.density = 4.000000000000000e+00f;
		fd.isSensor = bool(1);
		fd.filter.categoryBits = uint16(1);
		fd.filter.maskBits = uint16(65535);
		b2PolygonShape ps;
		ps.SetAsBox(area.w *0.5f * (float32)UtilityFunctions::P2M(), area.h *0.5f * (float32)UtilityFunctions::P2M());
		fd.shape = &ps;

		body->CreateFixture(&fd);
		body->SetUserData(data);

}
b2Body*Pool::createWood(float x,float y){
		b2BodyDef bd;
		bd.type = b2BodyType(2);
		bd.position.Set(x, y);
		bd.position *= (float32)UtilityFunctions::P2M();
		bd.allowSleep = bool(4);
		bd.awake = bool(2);
		bd.active = bool(32);
		bd.gravityScale = 1.000000000000000e+00f;
		b2Body*newBody = world->CreateBody(&bd);

		b2FixtureDef fd;
		fd.friction = 2.000000029802322e-01f;
		fd.density = 1.000000000000000e+00f;

		b2PolygonShape ps2;
		ps2.SetAsBox(size.w*0.5f*UtilityFunctions::P2M(), size.h*0.5f*0.6f*UtilityFunctions::P2M());
		fd.shape = &ps2;
		newBody->CreateFixture(&fd);
		newBody->SetUserData(data2);
		return newBody;
}
