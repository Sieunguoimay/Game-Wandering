#pragma once
#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include"Map.h"
#include"Camera.h"
#include"Button.h"
#include"SoundContainer.h"
#include"SettingScreen.h"
#include"TouchManager.h"

class MenuManager{
public:
	MenuManager(Map*map, Window*window,
		std::vector<Texture*>*textureCollection,
		SoundContainer*soundCollection);
	
	~MenuManager();

	void display();
	void handleEvent(TouchManager*touchManager);
	bool hasSelected()const;
	bool exitGameNow()const;
	
private:
	void setup();
	std::vector<ButtonOnePress*>buttons;
	
	ButtonOnePress*exitButton;
	ButtonOnePress*settingButton;

	LinkedList<SettingScreen*>settingScreen;
	
	Map*map;
	Size*windowSize;
	SoundContainer*soundCollection;
	std::vector<Texture*>*textureCollection;
	Window*window;
	bool selected;
};

#endif // !MENUMANAGER_H
