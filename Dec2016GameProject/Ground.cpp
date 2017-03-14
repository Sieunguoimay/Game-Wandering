#include "Ground.h"



Ground::Ground(b2World*world,Texture*texture)
	:world(world),texture(texture)
{
	size.set(51.0f, 51.0f);
}


Ground::~Ground()
{
	for (Node<Brick*>*iter = 
		bricks.getFirstNode(); iter != bricks.tail; iter = iter->next) {
		delete iter->data;
		iter->data = NULL;//to be safe
	}
	size.set(0,0);
	texture = NULL;
	world =NULL;
}

void Ground::display(const Camera&camera)
{
	for (Node<Brick*>*iter = bricks.getFirstNode(); iter != bricks.tail; iter = iter->next) 
		iter->data->display(camera);
}


Size  Ground::getSize() const
{
	// TODO: insert return statement here
	return size;
}

void Ground::putNewBrick(float x, float y,int type, bool leftOrRight)
{
	Brick*newBrick = new Brick(x,y,size.w,size.h,type,world,texture);
	if (newBrick){	
		if (leftOrRight)
			bricks.addFirst(newBrick);//right
		else
			bricks.addLast(newBrick);//left
	}
	
}

void Ground::delBrick(bool leftOrRight)
{
	if (leftOrRight) {
		delete bricks.getFirstNode()->data;
		bricks.getFirstNode()->data = NULL;
		bricks.delFist();//right
	}
	else {
		delete bricks.tail->prev->data;
		bricks.tail->prev->data = NULL;
		bricks.delLast();//left	
	}
}


