#include"GearMachine.h"

GearMachine::GearMachine(float x,float y,int numberGear,
	b2World*world,std::vector<Texture*>*textureCollection)
	:world(world),numberGear(numberGear),textureCollection(textureCollection)
{
	position.set(x,y);
	speedRate = 0.25f;
	radius = 40.0f;
	dead = false;
	
	b2BodyDef bd;
	bd.position.Set(position.x*UtilityFunctions::P2M(), 
					position.y*UtilityFunctions::P2M());
	bd.type = b2_staticBody;
	root= world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(10.0f*UtilityFunctions::P2M(), 10.0f * UtilityFunctions::P2M());//any size is ok - cause we only need the staticbody
	
	b2FixtureDef fd;
	fd.shape = &ps;
	fd.isSensor = true;
	root->CreateFixture(&fd);
	for (int i = 0; i < numberGear; i++)
		addNew();
}
GearMachine::~GearMachine(){
	position.set(0.0f,0.0f);
	for(Node<Gear*>*iter =gears.getFirstNode();iter!=gears.tail;iter=iter->next)
	{
		delete iter->data;
		iter->data= NULL;
	}
	world->DestroyBody(root);
	root= NULL;
	textureCollection = NULL;
}
void GearMachine::display(const Camera&camera){
	textureCollection->at(6)->render(camera,
		position.x - 10.0f - camera.getPosition().x,
		position.y - 10.0f - camera.getPosition().y, 20.0f, 20.0f);

	for (Node<Gear*>*iter = gears.getFirstNode(); iter != gears.tail; iter = iter->next)
		iter->data->display(camera);
	if(position.x<camera.getPosition().x-WINDOWSIZE_W*1.5f||
		position.x>camera.getPosition().x+WINDOWSIZE_W*2.5f)
		dead = true;
}
Vector2D GearMachine::getPosition(){
	return position;
}
void GearMachine::addNew(){

	int sign = 0;
	if (numberGear == 1)
		sign = 1;
	else sign = ((rand() % 10) > 5 ? 1 : -1);

	speedRate *= (float)(1.25*sign);
	radius -= 2.0f;
	Gear*newGear = NULL;
	
	if(gears.getSize() == 0)
	{
		newGear = new Gear(position.x,position.y,radius,
			world,textureCollection->at(6),textureCollection->at(5));
		newGear->connect(root,speedRate*3.141592f);
	}else {
		newGear = new Gear(
			gears.getFirstNode()->data->position2.x,
			gears.getFirstNode()->data->position2.y,radius,
			world,textureCollection->at(6),textureCollection->at(5));
		newGear->connect(gears.getFirstNode()->data->body1,speedRate*3.141592f);
	}
	gears.addFirst(newGear);
}
