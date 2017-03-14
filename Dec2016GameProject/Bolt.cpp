#include"Bolt.h"


Bolt::Bolt(b2World*world,Texture*texture,Texture*texturePointerToCloud,Sound*sound)
	:world(world),texture(texture),texturePointerToCloud(texturePointerToCloud),
	sound(sound)
{
	data = new ObjectData(SomeDefine::LIGHTNING_KILLER,NULL);
	shutle = path.head;

}
Bolt::~Bolt(){
	
	for (Node<Vector2D*>*iter = path.getFirstNode(); iter != path.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = path.delNode(iter);
	}
	for (Node<b2Body*>*iter = bodies.getFirstNode(); iter != bodies.tail; iter = iter->next)
	{
		world->DestroyBody(iter->data);
		iter->data = NULL;
		iter = bodies.delNode(iter);
	}
	delete data;
	data = NULL;
	
	shutle = NULL;
	texture = NULL;
	sound = NULL;
	world = NULL;
}
void Bolt::display(const Camera&camera){
	if(!path.isEmpty()){
		shutle = shutle->next;
		if (shutle->next != path.tail){
			bodies.addFirst(addNewParticleBody(shutle->next->data->x, shutle->next->data->y));
			for (Node<Vector2D*>*iter = path.getFirstNode(); iter != shutle->next; iter = iter->next)
				drawLine(*iter->data, *iter->next->data, camera);
		}else{
			for (Node<Vector2D*>*iter = path.getFirstNode(); iter != path.tail; iter = iter->next)
			{
				delete iter->data;
				iter->data =NULL;
			}
			
			for (Node<b2Body*>*iter = bodies.getFirstNode(); iter != bodies.tail; iter = iter->next)
			{
				world->DestroyBody(iter->data);
				iter->data = NULL;
			}
			path.emptyList();
			bodies.emptyList();
			shutle = path.head;
		}
		texturePointerToCloud->setColor(0xff, 0xee, 0x77);

	}
}
	

void Bolt::calculateDischarge(Vector2D cloudPosition,Vector2D target,bool beingShown){
	if(path.isEmpty()){
		float y = cloudPosition.y;
		float tempTarget = cloudPosition.x;
		float height = (target.y > y?(target.y-y):(y-target.y));
		float middle = y + height*0.5f;
		float width = height*0.5f;
		while(y<target.y){
			
			tempTarget += 0.1f*(target.x - tempTarget);
			float w = width - fabsf(middle - y);
			float deltaX = (float)((int)w > 0 ? (rand() % (int)w) : 0);
			float x = tempTarget +deltaX- w*0.5f;
			int tempInt = (int)(height / 15.0f+deltaX*0.5f);
			y += (tempInt>0?(rand() % tempInt) : 0) + 1.0f;
		
			path.addLast(new Vector2D(x,y));
		}

		//sound is played here
		if (beingShown)
			sound->play();
	}
}


void Bolt::drawLine(Vector2D&pos1, Vector2D & pos2, const Camera&camera)
{
	static float w = 4.0f;
	Vector2D temp = Vector2D::subtract(pos2, pos1);
	float angle = temp.getAngle();
	float h = temp.magnitude();
	texture->render(camera,
		(pos1.x + pos2.x) *0.5f - w*0.5f - camera.getPosition().x,
		(pos1.y + pos2.y) *0.5f - h*0.5f - camera.getPosition().y,
		1.0f, h, 0,angle-PI*0.5f);
}

b2Body * Bolt::addNewParticleBody(float x, float y)
{

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(x*UtilityFunctions::P2M(), y*UtilityFunctions::P2M());
	bd.gravityScale = 0.0f;
	b2Body*newBody = world->CreateBody(&bd);
	b2CircleShape cs;
	cs.m_radius = 4.0f * UtilityFunctions::P2M();

	b2FixtureDef fd;
	fd.shape = &cs;
	fd.isSensor = true;

	newBody->CreateFixture(&fd);
	newBody->SetUserData(data);
	return newBody;
}

