#include"GroupOfCloud.h"


GroupOfCloud::GroupOfCloud(float x,float y,float w, float h,std::vector<Texture*>*textureCollection,
SoundContainer*soundCollection)

{
	rectangle.set(x,y,w,h);
	
	int randNum = ((int)(rectangle.w / 100)>0 ? rand() % (int)(rectangle.w / 100) : 0) + 5;
	for (int i = 0; i < randNum; i++) {
		Cloud*newCloud = new Cloud(
		rectangle.x + (float)(rand() % (int)rectangle.w),
		rectangle.y + (float)(rand() % (int)rectangle.h), 
		textureCollection->at(16));
		clouds.addFirst(newCloud);
	}

}

GroupOfCloud::~GroupOfCloud(){
	for(Node<Cloud*>*iter = clouds.getFirstNode(); iter!= clouds.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = clouds.delNode(iter);
	}
	
}

void GroupOfCloud::display(const Camera&camera){
	for(Node<Cloud*>*iter = clouds.getFirstNode(); iter!= clouds.tail; iter = iter->next)
	{
		iter->data->blow(clouds);
		iter->data->stayWithinValleyArea(rectangle.x,rectangle.y,rectangle.w,rectangle.h);
		iter->data->display(camera);
	}
}
/////////////////////////////////////////////
/////////////////////////////////////////////



GroupOfDarkCloud::GroupOfDarkCloud(float x,float y,float w, float h,
	b2World*world,
	std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:world(world)
{
	isThereNewTarget = false;
	rectangle.set(x,y,w,h);
	int randNum = ((int)(rectangle.w/100)>0 ? rand() % (int)(rectangle.w / 100) : 0) + 5;
	for (int i = 0; i < randNum; i++)
		clouds.addFirst(new DarkCloud(
			x+rand()%(int)w,
			y+((int)(h/3.0f)>0?rand()%(int)(h/3.0f):0),
			world,textureCollection->at(16),textureCollection->at(18),
			soundCollection->at(1)));


	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(
	(rectangle.x+rectangle.w*0.5f)*UtilityFunctions::P2M(),
	 (rectangle.y+rectangle.h*0.5f)*UtilityFunctions::P2M());
	bd.gravityScale = 0;
	body = world->CreateBody(&bd);

	b2PolygonShape ps;
	ps.SetAsBox(
		rectangle.w*0.5f * UtilityFunctions::P2M(),
	 	rectangle.h*0.5f * UtilityFunctions::P2M());
	
	b2FixtureDef fd;
	fd.isSensor = true;
	fd.shape = &ps;
	body->CreateFixture(&fd);
	data = new ObjectData(SomeDefine::VALLEY_ID,this);
	body->SetUserData(data);
}

GroupOfDarkCloud::~GroupOfDarkCloud(){
	for (Node<Cloud*>*iter = clouds.getFirstNode();iter != clouds.tail; iter = iter->next)
	{
		delete ((DarkCloud*)(iter->data));
		iter->data = NULL;
	}
	world->DestroyBody(body);
	body = NULL;
	delete data;
	data = NULL;
}
void GroupOfDarkCloud::display(const Camera&camera){
	for (Node<Cloud*>*iter = clouds.getFirstNode(); iter != clouds.tail; iter = iter->next) {
		iter->data->blow(clouds);
		iter->data->stayWithinValleyArea(rectangle.x, rectangle.y, rectangle.w, rectangle.h/3);		
		((DarkCloud*)iter->data)->display(camera);
		
		if( isThereNewTarget){
			((DarkCloud*)(iter->data))->addNewTarget(newTarget.x,newTarget.y);
		}		
	}
	isThereNewTarget = false;

}
void GroupOfDarkCloud::findOut(Vector2D position){
	isThereNewTarget = true;
	newTarget.set(position);
}
