#pragma once
#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H
#include"Button.h"

#include"TouchManager.h"
#include"SettingScreen.h"
class PauseScreen
{
public:
	PauseScreen(Window*window,
		std::vector<Texture*>*textureContainer, 
		SoundContainer*soundCollection);
	~PauseScreen();

	void handleEvent(TouchManager*touchManager);
	void display();
	bool selected()const;
	bool resume()const;
	bool backHome()const;
	bool setting()const;
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleraion;

	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;

	ButtonOnePress homeButton;
	ButtonOnePress resumeButton;
	ButtonOnePress settingButton;
	LinkedList<SettingScreen*>settingScreen;

	Texture*background;
	Size*cameraSize;
	Window*window;
};

#endif // !PAUSESCREEN_H
