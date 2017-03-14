#include"Pole.h"
Pole::Pole(float x,float y,Texture*texture)
:texture(texture)
{
	position.set(x,y);
	size.set(150.0f,texture->getSize()->h*150.0f/texture->getSize()->w);
	position2.set(x,y-size.h);
}
Pole::~Pole(){
	texture = NULL;
}
void Pole::display(const Camera&camera){
	
	texture->render(camera,
		position2.x - size.w*0.5f - camera.getPosition().x,
		position2.y - camera.getPosition().y,
		size.w, size.h);
}

Vector2D Pole::getPosition(){
	return position2;
}
float Pole::getHeight(){
	return size.h;
}
