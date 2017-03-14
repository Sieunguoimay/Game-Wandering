#pragma once
#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H
#include"Button.h"
#include"SoundContainer.h"
#include"TouchManager.h"
class SoundController
{
public:
	SoundController(
		float x,float y,
		float volume, 
		Texture*buttonTexture, 
		Texture*movingButtonTexture,
		Texture*frameTexture,
		Texture*dynamicTexture,
		SoundContainer*soundCollection);
	~SoundController();
	void handleEvent(TouchManager*touchManager);
	void display();
	float getVolume()const;
	Vector2D position;

private:
	void setup(float x, float y, float size);
	//buttons
	ButtonOnePress button;
	ButtonControl movingButton;
	ButtonOnePress frameButton;
	
	Sound*sound;	
	Texture*dynamicTexture;
	float volume;
	bool switchOnOff;
};

#endif // !SOUNDCONTROLLER_H
