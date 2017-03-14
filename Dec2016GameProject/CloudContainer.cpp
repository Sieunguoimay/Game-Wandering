#include"CloudContainer.h"

CloudContainer::CloudContainer(b2World*world,std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:world(world),textureCollection(textureCollection),soundCollection(soundCollection)
	{
		
}
CloudContainer::~CloudContainer(){
	for(Node<GroupOfCloud*>*iter = groups.getFirstNode(); iter!= groups.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = groups.delNode(iter);
	}
	
	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter!= marks.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = marks.delNode(iter);
	}
	
	for(Node<GroupOfDarkCloud*>*iter = groups2.getFirstNode(); iter!= groups2.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = groups2.delNode(iter);
	}
	
	for(Node<Vector2D*>*iter = marks2.getFirstNode(); iter!= marks2.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
		iter = marks2.delNode(iter);
	}
	
	textureCollection = NULL;
	soundCollection = NULL;
}	
void CloudContainer::display(const Camera&camera){
	for(Node<GroupOfCloud*>*iter = groups.getFirstNode(); iter!= groups.tail; iter = iter->next)
	{
		iter->data->display(camera);
		//if(iter->data->rectangle.x>WINDOWSIZE*2.0f)
	}
	
	
	for(Node<GroupOfDarkCloud*>*iter = groups2.getFirstNode(); iter!= groups2.tail; iter = iter->next)
	{
		iter->data->display(camera);
		//if(iter->data->rectangle.x>WINDOWSIZE*2.0f)
	}
}
void CloudContainer::addNew(float x,float y){
	for(Node<GroupOfCloud*>*iter = groups.getFirstNode(); iter!= groups.tail; iter = iter->next)
		if(x>=iter->data->rectangle.x&&
			x<=iter->data->rectangle.x +iter->data->rectangle.w)
			return;
	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter!= marks.tail; iter = iter->next)
		if(iter->data->x==x)
			return;
	marks.addFirst(new Vector2D(x,y));
	if(marks.getSize()==2){
		float x1 = marks.getFirstNode()->data->x;
		float y1 = marks.getFirstNode()->data->y;
		
		float x2 = marks.getFirstNode()->next->data->x;
		float y2 = marks.getFirstNode()->next->data->y;
		delete marks.getFirstNode()->data;
		delete marks.getFirstNode()->next->data;
		marks.emptyList();
		
		float x = (x1<x2?x1:x2);
		float y = (y1<y2?y1:y2);
		float w = (x1<x2?(x2-x1):(x1-x2));
		float h = (y1<y2?(y2-y1):(y1-y2));
		
		GroupOfCloud*newGroup = new GroupOfCloud(x,y,w,h,textureCollection,soundCollection);
		groups.addFirst(newGroup);
	}
}

void CloudContainer::addNewDark(float x,float y){
	for(Node<GroupOfDarkCloud*>*iter = groups2.getFirstNode(); iter!= groups2.tail; iter = iter->next)
		if(x>=iter->data->rectangle.x&&
			x<=iter->data->rectangle.x +iter->data->rectangle.w)
			return;
	for(Node<Vector2D*>*iter = marks2.getFirstNode(); iter!= marks2.tail; iter = iter->next)
		if(iter->data->x==x)
			return;

	marks2.addFirst(new Vector2D(x,y));
	if(marks2.getSize()==2){
		float x1 = marks2.getFirstNode()->data->x;
		float y1 = marks2.getFirstNode()->data->y;
		
		float x2 = marks2.getFirstNode()->next->data->x;
		float y2 = marks2.getFirstNode()->next->data->y;
		delete marks2.getFirstNode()->data;
		delete marks2.getFirstNode()->next->data;
		marks2.emptyList();
		
		float x = (x1<x2?x1:x2);
		float y = (y1<y2?y1:y2);
		float w = (x1<x2?(x2-x1):(x1-x2));
		float h = (y1<y2?(y2-y1):(y1-y2));
		
		GroupOfDarkCloud*newGroup = 
			new GroupOfDarkCloud(x,y,w,h,world,textureCollection,soundCollection);
		groups2.addFirst(newGroup);
	}
}
