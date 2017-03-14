#include "Poster.h"



Poster::Poster(Size*windowSize, Texture*texture, 
	Texture*texturePressAnyKey, SoundContainer*soundCollection)
	:windowSize(windowSize),texture(texture),
	texturePressAnyKey(texturePressAnyKey),
	soundCollection(soundCollection)
{
	done = false;
	keyPressed = false;

	velY = 0.0f;
	oscilationY = -texturePressAnyKey->getSize()->h;
	angle = 0.0f; 
}


Poster::~Poster()
{
	velY = 0.0f;
	keyPressed = false;
	done = false;
	texture = NULL;
	texturePressAnyKey = NULL;
	soundCollection = NULL;
}

void Poster::handleEvent(TouchManager*touchManager)
{
	for(int i = 0; i<4;i++){
		if(touchManager->tfingers.at(i).type == FINGERDOWN){
				soundCollection->at(13)->play();
				keyPressed = true;
		}		
	}
}

void Poster::display()
{
	int x = 0;
	texture->render(x,position.y,(int)windowSize->w,(int)windowSize->h,0);
	
	texturePressAnyKey->render(
		(int)(windowSize->w *0.5f - texturePressAnyKey->getSize()->w *0.5f),
		(int)oscilationY, 
	 	(int)texturePressAnyKey->getSize()->w, (int)texturePressAnyKey->getSize()->h,0);
	
	if (keyPressed) {
		float dest = -windowSize->h;
		velY = 0.1f*(dest - position.y);
		if (velY > -5.0f)
			velY = -5.0f;
		position.y += velY;
		oscilationY += velY;
		if (position.y <= dest)
			done = true;
	}
	else {
		angle += 0.02f;
		if (angle >= 2.0f*PI)
			angle = 0.0f;
		oscilationY = windowSize->h*0.9f + sinf(angle)*texturePressAnyKey->getSize()->h;
	}
	
}

void Poster::up()
{
	soundCollection->at(13)->play();
	keyPressed = true;
}

bool Poster::hasDone()
{
	return done;
}
