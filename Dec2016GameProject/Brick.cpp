#include "Brick.h"


Brick::Brick(float x, float y,float w, float h,
	int typeBrick,b2World*world,Texture*texture)
	:world(world),texture(texture),typeBrick(typeBrick)
{
	size.set(w,h);
	data = new ObjectData(-1, NULL);	
	this->typeBrick = typeBrick;
	if (typeBrick == 0) {
		data->ID = SomeDefine::UNDERGROUND_BRICK_ID;
		createBodyBrick(x, y, size.w, size.h, false);
	}
	else if (typeBrick == 1) {

		data->ID = SomeDefine::SURFACE_BRICK_ID;
		createBodyBrick(x, y, size.w, size.h, false);
	}
	else if (typeBrick == 2) {
		createBodyBrick(x, y, size.w, size.h, true);
		return;
	}
	body->SetUserData(data);
}

Brick::~Brick()
{
	size.set(0,0);
	typeBrick  = 0;
	world->DestroyBody(body);
	body = NULL;
	delete data;
	data = NULL;
	world = NULL;
}
void Brick::display(const Camera&camera){
	b2Vec2 pos = body->GetPosition();
	texture->render(camera,
			(pos.x*UtilityFunctions::M2P() - size.w *0.5f - camera.getPosition().x),
			(pos.y*UtilityFunctions::M2P() - size.h *0.5f - camera.getPosition().y),
			size.w,
			size.h,
			typeBrick,
			 0, false);
}

void Brick::createBodyBrick(float x, float y, float w, float h,bool isSensor)
{
	b2BodyDef bd;
	bd.type = b2_staticBody;
	bd.position.Set(x*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(w*0.5f*UtilityFunctions::P2M(), h*0.5f*UtilityFunctions::P2M());

	b2FixtureDef fd;
	fd.shape = &ps;
	if (isSensor)
		fd.isSensor = true;
	body->CreateFixture(&fd);
}
