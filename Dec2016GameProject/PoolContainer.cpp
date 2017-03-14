#include"PoolContainer.h"

PoolContainer::PoolContainer(b2World*world,std::vector<Texture*>*textureCollection)
:world(world),textureCollection(textureCollection)
{
	
}

PoolContainer::~PoolContainer(){

	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter!= marks.tail; iter= iter->next){
		delete iter->data;
		iter->data = NULL;
		iter= marks.delNode(iter);
	}
	
	for(Node<Pool*>*iter = pools.getFirstNode(); iter!= pools.tail; iter= iter->next){
		delete iter->data;
		iter->data = NULL;
		iter= pools.delNode(iter);
	}
	textureCollection = NULL;
	world = NULL;
}
void PoolContainer::display(const Camera&camera){
	for(Node<Pool*>*iter = pools.getFirstNode(); iter!= pools.tail; iter= iter->next){
		iter->data->display(camera);
		if(iter->data->area.x+iter->data->area.w<
			camera.getPosition().x-WINDOWSIZE_W*1.5f
			||iter->data->area.x>camera.getPosition().x+WINDOWSIZE_W*2.5f){
			delete iter->data;
			iter->data = NULL;
			iter= pools.delNode(iter);
		}
	}
}
void PoolContainer::addNew(float x,float y,float size,int type){
	
	for(Node<Pool*>*iter = pools.getFirstNode(); iter!= pools.tail; iter= iter->next)
		if(x-size*0.5f==iter->data->area.x
		||x+size*0.5f==iter->data->area.x+iter->data->area.w)
			return;
	for(Node<Vector2D*>*iter = marks.getFirstNode(); iter!= marks.tail; iter= iter->next)
		if(iter->data->x==x)
			return;
			
	marks.addFirst(new Vector2D(x,y));
	if(marks.getSize()==2){
		float x,y,w,h;
		if(marks.getFirstNode()->data->x<marks.getFirstNode()->next->data->x)
		{
			x = marks.getFirstNode()->data->x;
			y = marks.getFirstNode()->data->y;
			w = marks.getFirstNode()->next->data->x-marks.getFirstNode()->data->x;
			h = marks.getFirstNode()->next->data->y-marks.getFirstNode()->data->y;
		}
		else{
			
			x = marks.getFirstNode()->next->data->x;
			y = marks.getFirstNode()->next->data->y;
			w = marks.getFirstNode()->data->x - marks.getFirstNode()->next->data->x;
			h = marks.getFirstNode()->data->y-marks.getFirstNode()->next->data->y;
		}
		if(type==0)
			pools.addFirst(new Pool(x-size*0.5f,y-size*0.5f,w+size,h+size,world,textureCollection->at(13),
				textureCollection->at(14),textureCollection->at(15),false));
		else if(type == 1)
			pools.addFirst(new Pool(x-size*0.5f,y-size*0.5f,w+size,h+size,world,textureCollection->at(13),
				textureCollection->at(14),textureCollection->at(15),true));
		else if(type == 2)
			pools.addFirst(new Pool(x-size*0.5f,y-size*0.5f,w+size,h+size,world,textureCollection->at(13),
				textureCollection->at(14),textureCollection->at(15),false,true));

		delete  marks.getFirstNode()->data;
		delete  marks.getFirstNode()->next->data;
		marks.emptyList();
	}
}
