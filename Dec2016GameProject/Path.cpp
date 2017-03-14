#include"Path.h"

Path::Path(float x,float y){
	position.set(x,y);
	radius = 20.0f;
	
	float angle = 0.0f;
	while(angle<3.141592f*2.0f) {
		angle += PI / 6.0f;
		Vector2D*newVertice = UtilityFunctions::polarToCartesian(position,50.0f, angle);
		paths.addFirst(newVertice);
	}
	paths.addFirst(paths.tail->prev->data);
}
Path::~Path(){
	for (Node<Vector2D*>*iter = paths.getFirstNode()->next; iter != paths.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	radius = 0.0f;
	position.set(0.0f,0.0f);
}
