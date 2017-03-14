#include"BridgeContainer.h"

BridgeContainer::BridgeContainer(b2World*world,
	std::vector<Texture*>*textureCollection)
	:world(world),textureCollection(textureCollection)
{
		
}
BridgeContainer::~BridgeContainer(){
	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter != marks.tail; iter= iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	for(Node<Bridge*>*iter = bridges.getFirstNode(); iter != bridges.tail; iter= iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter= bridges.delNode(iter);
	}
	
	world = NULL;
	textureCollection = NULL;
}
void BridgeContainer::display(const Camera&camera){
	for(Node<Bridge*>*iter = bridges.getFirstNode(); iter != bridges.tail; iter= iter->next)
	{
		iter->data->display(camera);
		if(iter->data->done()){
			delete iter->data;
			iter->data  = NULL;
			iter= bridges.delNode(iter);
		}
	}
}
void BridgeContainer::addNew(float x,float y){
	for(Node<Bridge*>*iter = bridges.getFirstNode(); iter != bridges.tail; iter= iter->next)
		if(x==iter->data->x1||x==iter->data->x2)
			return;
	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter != marks.tail; iter= iter->next)
		if(iter->data->x==x)
			return;
	
	marks.addFirst(new Vector2D(x,y));
	if(marks.getSize()==2){
		Vector2D position1;
		Vector2D position2;
		if(marks.getFirstNode()->data->x>marks.getFirstNode()->next->data->x){
			position1 = marks.getFirstNode()->next->data;
			position2 = marks.getFirstNode()->data;
		}else{
			position2 = marks.getFirstNode()->next->data;
			position1 = marks.getFirstNode()->data;
		}
		Bridge*newBridge = new Bridge(position1,position2,world,
		textureCollection->at(8),textureCollection->at(9));
		delete marks.getFirstNode()->next->data;
		delete marks.getFirstNode()->data;
		marks.emptyList();

		bridges.addFirst(newBridge);

	}
}
