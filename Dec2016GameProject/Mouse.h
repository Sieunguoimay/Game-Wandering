#pragma once
#ifndef MOUSE_H
#define MOUSE_H

#include"globalheader.h"
#include"TouchManager.h"
#include"Camera.h"
#include"Texture.h"
class Mouse
{
public:
	Mouse(Texture*texture);
	~Mouse();
	void handleEvent(TouchManager*touchManager);
	void display(const Camera&camera);
private:
	Texture*texture;
	Vector2D position;
	Size size;
	int index;
};

#endif // !MOUSE_H
