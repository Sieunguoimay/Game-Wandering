#include "MenuManager.h"



MenuManager::MenuManager(Map*map, Window*window,
	std::vector<Texture*>*textureCollection,
	 SoundContainer*soundCollection)
	:map(map),windowSize(window->getWindowSize()),
	window(window),
	soundCollection(soundCollection),
	textureCollection(textureCollection)
{
	soundCollection->playMusicLoopForever();
	
	selected = false;
	exitButton = new ButtonOnePress(
		window->getWindowSize()->w*0.9f,
		window->getWindowSize()->h*0.15f,
		50.0f,
		 50.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(24));
		
	settingButton = new ButtonOnePress(
		exitButton->getRectangle().x, 
		exitButton->getRectangle().y+ exitButton->getRectangle().w*1.5f,
		exitButton->getRectangle().w, 
		exitButton->getRectangle().h,
		soundCollection->at(4), 
		soundCollection->at(7),
		textureCollection->at(28));
	setup();
	
}


MenuManager::~MenuManager()
{
	delete exitButton;
	delete settingButton;
	Mix_HaltMusic();
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons.at(i);
		buttons.at(i) = NULL;
	}
	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	soundCollection = NULL;
}

void MenuManager::setup()
{

	float buttonSize = 120.0f;
	int numberButton = NUM_MAP_LEVEL;
	float buttonDistance = buttonSize*1.2f;
	float x = windowSize->w/3.20f;
	float y = windowSize->h * 2.0f/ 3.0f;
	
	for (int i = 0; i < numberButton; i++) {
		if (i < map->getMapLevelSaved()+1)
			buttons.push_back(new ButtonOnePress(x + i*buttonDistance, y, buttonSize, buttonSize, 
				soundCollection->at(4),
				soundCollection->at(7),
				textureCollection->at(21)));
		else 
			buttons.push_back(new ButtonOnePress(x + i*buttonDistance, y, buttonSize, buttonSize, 
				soundCollection->at(4),
				soundCollection->at(7),
				textureCollection->at(21),true));
	}
}

void MenuManager::display()
{

	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		iter->data->display();
		if (iter->data->back()){
			delete iter->data;
			iter->data = NULL;
			iter = settingScreen.delNode(iter);
		}
		return;
	}

	int x = 0;
	textureCollection->at(23)->render(x, x,(int)windowSize->w, (int)windowSize->h,0);

	for (size_t i = 0; i < 4; i++) {
		buttons.at(i)->display();
		if (buttons.at(i)->isPressed())
		{
			map->setMapLevel(i);
			selected = true;
		}
		textureCollection->at(22)->render(
			(int)(buttons.at(i)->getRectangle().x - buttons.at(i)->getRectangle().w / 4), 
			(int)(buttons.at(i)->getRectangle().y + buttons.at(i)->getRectangle().h*0.5), 
			(int)(buttons.at(i)->getRectangle().w/2),
			(int)( buttons.at(i)->getRectangle().h/2),i);
	}
	
	exitButton->display();
	settingButton->display();
}

void MenuManager::handleEvent(TouchManager*touchManager)
{
	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		iter->data->handleEvent(touchManager);
		return;
	}
	int  i = 0;
		if (settingButton->checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
		{
			if (touchManager->tfingers.at(i).type == FINGERDOWN)
				settingButton->press();
			settingButton->state = 1;
		}
		else settingButton->state = 0;
		if (exitButton->checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
		{
			if (touchManager->tfingers.at(i).type == FINGERDOWN)
				exitButton->press();
			exitButton->state = 1;
		}
		else exitButton->state = 0;
		for (size_t j = 0; j < buttons.size(); j++)
		
			if (buttons.at(j)->checkInside(
				touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
			{
				buttons.at(j)->state = 1;//hover

				if (touchManager->tfingers.at(i).type == FINGERDOWN)
					buttons.at(j)->press();
			}
			else buttons.at(j)->state = 0;

	
	if(settingButton->isPressed()){
		settingScreen.addFirst(
			new SettingScreen(window,textureCollection,soundCollection));
		settingButton->reset();	
	}
}

bool MenuManager::hasSelected() const
{
	return selected;
}

bool MenuManager::exitGameNow() const
{
	return exitButton->isPressed();
}
