#include "SettingScreen.h"



SettingScreen::SettingScreen(Window*window,
	std::vector<Texture*>*textureCollection, SoundContainer*soundCollection)

	:cameraSize(window->getWindowSize()),window(window),textureCollection(textureCollection),
	
	backButton(window->getWindowSize()->w*0.2f, window->getWindowSize()->h*0.2f, 80.0f,
		80.0f / textureCollection->at(29)->getSize()->w*textureCollection->at(29)->getSize()->h,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(29)),
	
	fullScreenButtonOn(window->getWindowSize()->w*0.8f,
		window->getWindowSize()->h*0.2f, 80.0f, 80.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(40)),

	fullScreenButtonOff(window->getWindowSize()->w*0.8f,
		window->getWindowSize()->h*0.2f, 80.0f, 80.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(41)),

	chunkController(
		window->getWindowSize()->w*0.3f,
		window->getWindowSize()->h *0.42f,
		(float)Mix_Volume(-1,-1), 
		textureCollection->at(30), 
		textureCollection->at(33),
		textureCollection->at(32),
		textureCollection->at(38),soundCollection),
	
	musicController(
		window->getWindowSize()->w*0.3f,
		window->getWindowSize()->h *0.68f,
		//128,
		(float)Mix_VolumeMusic(-1), 
		textureCollection->at(31), 
		textureCollection->at(33), 
		textureCollection->at(32), 
		textureCollection->at(38),soundCollection)
			
{
	fullScreenPointer = &fullScreenButtonOn;
	backNow = false;
}


SettingScreen::~SettingScreen()
{
	fullScreenPointer = NULL;
	backNow = false;
	window = NULL;
}

void SettingScreen::handleEvent(TouchManager*touchManager)
{
		//handle touche Events for some buttons
	int i = 0;
			if(backButton.checkInside(touchManager->tfingers.at(i).x,touchManager->tfingers.at(i).y)){
				if (touchManager->tfingers.at(i).type == FINGERDOWN)
					backButton.press();
				backButton.state = 1;
			}
			else backButton.state = 0;
			if (fullScreenPointer->checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
		{
			if (touchManager->tfingers.at(i).type == FINGERDOWN)
				fullScreenPointer->press();
			fullScreenPointer->state = 1;
		}
			else
			fullScreenPointer->state = 0;

			if (fullScreenPointer->isPressed())
			{
				fullScreenPointer = ((fullScreenPointer == &fullScreenButtonOff) ? &fullScreenButtonOn : &fullScreenButtonOff);
				window->setFullScreen(!window->isFullScreen());
			}
	if(backButton.isPressed())
		backNow = true;
		
	chunkController.handleEvent(touchManager);
	musicController.handleEvent(touchManager);
	
	
	Mix_Volume(-1, (int)chunkController.getVolume());
	Mix_VolumeMusic((int)musicController.getVolume());
}

void SettingScreen::display()
{
	
	int x = 0;
	textureCollection->at(38)->setColor(215,154, 67);
	textureCollection->at(38)->render(x, x, (int)cameraSize->w, (int)cameraSize->h, 0);
	textureCollection->at(38)->setColor(0xff, 0xff, 0xff);

	chunkController.display();
	musicController.display();
	
	backButton.display();
	fullScreenPointer->display();

	textureCollection->at(39)->setColor(156, 106, 34);
	textureCollection->at(39)->render(x, x, (int)cameraSize->w, (int)cameraSize->h, 0);
	textureCollection->at(39)->setColor(0xff, 0xff, 0xff);

}

bool SettingScreen::back() const
{
	return backNow;
}
