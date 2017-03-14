#include "Mover.h"



Mover::Mover(b2World*world,std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:world(world),textureCollection(textureCollection),
	soundCollection(soundCollection)
{
	jumpPressed = false;
	minJumpDuration = 0;
	onGroundCounter = 0;
	walkLeftPressed = false;
	walkRightPressed = false;
	firePressed = false;
	exploded = false;
	dead = false;

	//some constants don't need to be reseted
	size.set(50.0f, 50.0f);
	maxSpeed = 8.0f;//m/s
	jumpForce = new b2Vec2(0.0f, -100.0f);
	//mass = 500.0f;
	friction = 3.5f;
	radius = (size.w + size.h)*0.5f;//radius for set first world

	
	data = new ObjectData(SomeDefine::MOVERID, this);
	desiredVel = new Vector2D();
	staticPosition = new Vector2D(100.0f, 200.0f);//pixels - pixels
	

	createBody();
	body->SetUserData(data);
	skin = new Skin(textureCollection->at(47),
		textureCollection->at(48),textureCollection->at(49),
		&size,staticPosition);
	bunnyEar = new BunnyEar(radius*0.25f, radius*0.5f,world,body,
		textureCollection->at(50),textureCollection->at(3));

}


Mover::~Mover()
{
	world->DestroyBody(body);
	body = NULL;
	
	data->pointer = NULL;
	delete data;
	data = NULL;

	//this loop is used in case the program is stopped while explosion has not finished yet
	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	soundCollection = NULL;
	delete staticPosition;
	staticPosition = NULL;
	delete jumpForce;
	jumpForce = NULL;
	delete desiredVel;
	desiredVel = NULL;
	delete bunnyEar;
	bunnyEar = NULL;
	delete skin;
	skin=NULL;

	walkRightPressed = false;
	walkLeftPressed = false;
	jumpPressed = false;
	firePressed = false;
	exploded = false;
	dead = false;
}
void Mover::reset()
{
	staticPosition->set(100.0f, 200.0f);
	//the body that is do nothing here more than a mass
	world->DestroyBody(body);
	createBody();
	body->SetUserData(data);

	delete bunnyEar;
	bunnyEar = new BunnyEar(radius*0.25f, radius*0.5f,world,body,
	textureCollection->at(50),textureCollection->at(3));

	minJumpDuration = 0;
	onGroundCounter = 0;

	walkRightPressed = false;
	walkLeftPressed = false;
	jumpPressed = false;
	firePressed = false;
	exploded = false;
	dead = false;
}
void Mover::handleEvent(SDL_Event & mainEvent)
{

	if (mainEvent.type == SDL_KEYDOWN){
		if(mainEvent.key.keysym.sym== SDLK_UP|| mainEvent.key.keysym.sym==SDLK_w)
			jumpPressed = true;
		
		if (mainEvent.key.keysym.sym == SDLK_RIGHT || mainEvent.key.keysym.sym == SDLK_d)
			walkRightPressed = true;
		if (mainEvent.key.keysym.sym == SDLK_LEFT || mainEvent.key.keysym.sym == SDLK_a)
			walkLeftPressed = true;
		if (mainEvent.key.keysym.sym == SDLK_SPACE || mainEvent.key.keysym.sym == SDLK_RETURN)
			firePressed = true;
		}

	else if (mainEvent.type == SDL_KEYUP){
		if (mainEvent.key.keysym.sym == SDLK_UP || mainEvent.key.keysym.sym == SDLK_w)
			jumpPressed = false;

		if (mainEvent.key.keysym.sym == SDLK_RIGHT || mainEvent.key.keysym.sym == SDLK_d)
			walkRightPressed = false;
		if (mainEvent.key.keysym.sym == SDLK_LEFT || mainEvent.key.keysym.sym == SDLK_a)
			walkLeftPressed = false;
		if (mainEvent.key.keysym.sym == SDLK_SPACE || mainEvent.key.keysym.sym == SDLK_RETURN)
			firePressed = false;
	}
}
//display is the story occuring
void Mover::display(Camera&camera)
{
	if (!dead) {
		update();
		bunnyEar->display(camera);
	}
	skin->render(camera);

	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next)
	{
		iter->data->display(camera);
		if (iter->data->isDead()) {
			delete iter->data;
			iter = explosion.delNode(iter);
			exploded = true;//as the explosion finishs
		}
	}//update the  camera target inside this mover :)) 
		
	camera.setTarget(
		staticPosition->x,
		staticPosition->y);
}




//where everything update here
//this function is called inside the display()
void Mover::update()
{
	//update everything here
	staticPosition->set(
		body->GetPosition().x*UtilityFunctions::M2P(),
		body->GetPosition().y*UtilityFunctions::M2P());

	//as the fire button - space pressed - bunnyEar will discharge - create a new particle - System
	if (firePressed) {
		bunnyEar->discharge();//put it into the container
		firePressed = false;//set it tobe false right after that
		soundCollection->at(3)->play();
	}

	////////////////////////////////////////////////////////
	if (jumpPressed)//jumpPressed is true - jumping is false/0
	{
		if (onGroundCounter&& !minJumpDuration)
		{
			minJumpDuration = 10;
			body->ApplyForce(*jumpForce, body->GetWorldCenter(), true);
			soundCollection->at(8)->play();
		}

	}
	if (minJumpDuration > 0)//as it greater than 0 continue to decrease it to 0 - then it can jump
		minJumpDuration--;
	////////////////////////////////////////////////////////


	if (walkRightPressed || walkLeftPressed)//if key pressed
		walk(true);// walk and stoped is false
	//else - in this case as stoped is still not false let walk slow down
	else //if(!stoped)
		walk(false);
		
	//fall off the screen
	if (staticPosition->y> 2.0f * WINDOWSIZE_H)
		exploded = true;
}



//when mover die - this function is called outside by the monsters who keep a pointer to mover
//as being called it will create a new Explosion to put into the explosion container
//after the explosion is finished, the mover will reset itself
void Mover::die()
{
	if (!dead) {
		//printf("Game over.\n");
		Explosion*newExplosion = new Explosion();
		if (newExplosion) {
			newExplosion->setup(new Vector2D(staticPosition->x, staticPosition->y), 
			textureCollection->at(3), soundCollection->at(0));
			explosion.addFirst(newExplosion);
		}
		dead = true;
	}
}

//set target is a chain function between lightning inside bunnyEar with outside environment - target here is kinds of Monsters
void Mover::setTarget(Vector2D target)
{
	const float maxDistance = 500.0f*500.0f;
	float distanceSqr = Vector2D::distanceSqr(target, *staticPosition);
	if (distanceSqr < maxDistance)
		this->bunnyEar->setTarget(target);
}

float Mover::getRadarRadius() const
{
	return bunnyEar->getRadaRadius();
}

//walk - used to control the moving of mover
void Mover::walk(bool state)
{
	Vector2D velocity(body->GetLinearVelocity().x, body->GetLinearVelocity().y);
	if (state)//move your body
	{
		if (onGroundCounter)//let's update this in side the contact listener
		{
			desiredVel->set((walkLeftPressed ? -maxSpeed : maxSpeed), 0);
			//update skin's sprites
			skin->walk(velocity.x);
		}//in the air
		else desiredVel->set((walkLeftPressed ? -maxSpeed / 1.50f : maxSpeed / 1.50f), 0);
	}else //stop
		desiredVel->set(-velocity.x*friction, 0);
	//apply force for the body center??? what the fuck - dynamicbody???
	body->ApplyForce(b2Vec2(desiredVel->x - velocity.x, 0), body->GetWorldCenter(), true);
}

//tell the world that mover is dead or not
//if so, the world will call the reset function
const bool & Mover::hasExploded() const
{
	// TODO: insert return statement here
	return exploded;
}
//geth this fucking static position for what?
Vector2D * Mover::getPosition()
{
	return this->staticPosition;
}

//it is very good idea ==>>>>>>>
//why yoou don't think about it earlier?
//it's so simple and effective
//the problem is that the contact is between not only two but 3 or more
//there for we need the boolean counter
void Mover::setOnGround(bool state)
{
	if (state) {
		onGroundCounter++;
		if (onGroundCounter == 0)
			onGroundCounter = 1;
	}
	else {
		onGroundCounter--;
		if (onGroundCounter < 0)
			onGroundCounter = 0;
	}
}


//put here coz we rarly reach it

void Mover::createBody(){
	
	b2BodyDef bd;//position, type
	bd.position.Set(staticPosition->x*UtilityFunctions::P2M(), staticPosition->y*UtilityFunctions::P2M());
	bd.type = b2_dynamicBody;
	bd.fixedRotation = true;
	bd.gravityScale = 3;//who is heavier
	body = world->CreateBody(&bd);//each create a new body for the world

	b2CircleShape cs;
	cs.m_radius = radius*UtilityFunctions::P2M()/2;

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.density = 0.5f;
	fd.friction = 0.05f;
	fd.restitution = 0.1f;

	body->CreateFixture(&fd);
}
