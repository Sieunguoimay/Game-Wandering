#include"GearContainer.h"
GearContainer::GearContainer(b2World*world,std::vector<Texture*>*textureCollection)
:world(world),textureCollection(textureCollection)
{

}
GearContainer::~GearContainer(){
	for(Node<GearMachine*>*iter=gears.getFirstNode();iter!=gears.tail; iter=iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	world = NULL;
	textureCollection = NULL;
}
void GearContainer::display(const Camera&camera){
	for(Node<GearMachine*>*iter=gears.getFirstNode();iter!=gears.tail; iter=iter->next)
	{
		iter->data->display(camera);
		if(iter->data->dead){
			delete iter->data;
			iter->data = NULL;
			iter= gears.delNode(iter);
		}
	}
}
void GearContainer::addNew(float x,float y,int number){
	for(Node<GearMachine*>*iter=gears.getFirstNode();iter!=gears.tail; iter=iter->next)
		if(iter->data->getPosition().x==x)
			return;
	gears.addFirst(new GearMachine(x,y,number,world,textureCollection));	
}
