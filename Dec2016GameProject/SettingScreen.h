#pragma once
#ifndef SETTINGSCREEN_H
#define SETTINGSCREEN_H
#include"SoundContainer.h"
#include"SoundController.h"
#include"SDL_mixer.h"
#include"TouchManager.h"
#include"Window.h"
class SettingScreen
{
public:
	SettingScreen(Window*window,std::vector<Texture*>*textureCollection, SoundContainer*soundCollection);
	~SettingScreen();
	void handleEvent(TouchManager*touchManager);
	void display();
	bool back()const;

private:
	std::vector<Texture*>*textureCollection;
	
	SoundController chunkController;
	SoundController musicController;
	
	//buttons
	ButtonOnePress backButton;
	ButtonOnePress fullScreenButtonOn;
	ButtonOnePress fullScreenButtonOff;
	ButtonOnePress*fullScreenPointer;
	Window*window;
	Size*cameraSize;
	bool backNow;
};

#endif // !SETTINGSCREEN_H
