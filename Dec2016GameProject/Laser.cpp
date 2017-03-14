#include "Laser.h"





Laser::Laser(b2World * world, Texture * texture, Texture*texture2, Sound*sound, LinkedList<Photon*>*photonContainer)
	:world(world),texture(texture),texture2(texture2),sound(sound),photonContainer(photonContainer)
{
	switcher = true;
	data = new ObjectData(SomeDefine::SURFACE_BRICK_ID, NULL);
	beingShown = false;
	outOfScreen =false;
}

Laser::~Laser()
{
	world->DestroyBody(body);
	body = NULL;
	world = NULL;
	delete data;
	data = NULL;
	switcher = false;
	beingShown = false;
	outOfScreen =false;
}

void Laser::setup(float x, float y, int direction)
{
	float speed = 10.0f;
	time = 0;
	float velX = 0.0f;
	float velY = 0.0f;
	switch (direction) {
	case 1:
		velX = 0;
		velY = -speed;
		break;
	case 2:	
		velX = speed;
		velY = 0;
		break;
	case 3:
		velX = 0;
		velY = speed;
		break;
	case 4:
		velX = -speed;
		velY = 0;
		break;
	}
	position.set(x,y);
	velocity.set(velX,velY);
	size = 60.0f;
	
	b2BodyDef bd;
	bd.position.Set((x-size/2)*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());
	bd.type = b2_staticBody;
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(0.4f*size*UtilityFunctions::P2M(), 0.4f*size*UtilityFunctions::P2M());
	b2FixtureDef fd;
	fd.shape = &ps;

	body->CreateFixture(&fd);
	body->SetUserData(data);
}

void Laser::display(const Camera & camera)
{
	const int MAX_EMITION = 10;
	float frequency = 1;
	time += 1.0f / FPS;
	if (time > 1 / frequency) {
		time = 0;
		switcher = !switcher; 
		emitCouter = MAX_EMITION;

	}

	if (switcher)
	{
		if (emitCouter > 0) {
			if (emitCouter == MAX_EMITION) {
				if (beingShown)
					sound->play();
			}
			emitCouter--;
			emit();
		}
	}
	texture2->render(camera, position.x - size - camera.getPosition().x,
		 position.y - 30 - camera.getPosition().y, 60, 60);
	//update for sound to be displayed
	beingShown = (position.x > camera.getPosition().x&&
		position.x < camera.getPosition().x + WINDOWSIZE_W);
	outOfScreen = (position.x < camera.getPosition().x-WINDOWSIZE_W*1.5f&&
		position.x > camera.getPosition().x + 2.5f*WINDOWSIZE_W);

}	

void Laser::start()
{
	switcher = true;
}

void Laser::cease()
{
	switcher = false;
}


void Laser::emit()
{

	const float freq = 15;
	duration+=1.0f/FPS;
	if(duration<1.0f/freq)
		return;
	duration = 0.0f;
	
	
	photonContainer->addFirst(new Photon(position.x,position.y,world,texture));
	
}

