#include "Mouse.h"



Mouse::Mouse(Texture*texture)
	:texture(texture)
{
	position.set(WINDOWSIZE_W *0.5f, WINDOWSIZE_H*0.5f);
	index = 0;
	size.set(40.0f, 40.0f*texture->getSize()->h / texture->getSize()->w);
}


Mouse::~Mouse()
{
	index = 0;
	texture = NULL;
	position.set(0, 0);
	size.set(0, 0);
}

void Mouse::handleEvent(TouchManager * touchManager)
{
	position.set(touchManager->tfingers.at(0).x, touchManager->tfingers.at(0).y);
	if (touchManager->tfingers.at(0).type == FINGERDOWN)
		index = 1;
	else index = 0;
}

void Mouse::display(const Camera & camera)
{
	texture->render(camera, position.x, position.y, size.w, size.h, index);
}
