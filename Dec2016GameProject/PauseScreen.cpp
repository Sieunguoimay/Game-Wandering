#include "PauseScreen.h"



PauseScreen::PauseScreen(Window*window,
	std::vector<Texture*>*textureCollection,
	 SoundContainer*soundCollection)
	
	:cameraSize(window->getWindowSize()),
	textureCollection(textureCollection),
	soundCollection(soundCollection),
	
	position(-window->getWindowSize()->w*0.5f, 0.0f),
	velocity(50.0f, 0.0f),
	
	homeButton(-window->getWindowSize()->w*0.5f+ window->getWindowSize()->w*0.5f- window->getWindowSize()->w / 9.0f,
		window->getWindowSize()->h/2,
		window->getWindowSize()->w / 10.0f,
		window->getWindowSize()->w / 10.0f,
		soundCollection->at(4), 
		soundCollection->at(7),
		textureCollection->at(26)),
	
	resumeButton(-window->getWindowSize()->w*0.5f+ window->getWindowSize()->w*0.5f,
		window->getWindowSize()->h/2,
		window->getWindowSize()->w / 10.0f,
		window->getWindowSize()->w / 10.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(27)),
	
	settingButton(-window->getWindowSize()->w*0.5f+ window->getWindowSize()->w*0.5f + window->getWindowSize()->w / 9.0f,
		window->getWindowSize()->h*0.5f,
		window->getWindowSize()->w / 10.0f,
		window->getWindowSize()->w / 10.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		textureCollection->at(28))
	
{
	background = textureCollection->at(38);
}


PauseScreen::~PauseScreen()
{
	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	background = NULL;
	cameraSize = NULL;
}

void PauseScreen::handleEvent(TouchManager*touchManager)
{
	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		iter->data->handleEvent(touchManager);
		return;
	}
	int i = 0;
	if(settingButton.checkInside(touchManager->tfingers.at(i).x,touchManager->tfingers.at(i).y)){
		if (touchManager->tfingers.at(i).type == FINGERDOWN)
			settingButton.press();
		settingButton.state = 1;
	}
	else settingButton.state = 0;
	if (homeButton.checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
	{
		if (touchManager->tfingers.at(i).type == FINGERDOWN)
			homeButton.press();
		homeButton.state = 1;
	}
	else homeButton.state = 0;
	if (resumeButton.checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
	{
		if (touchManager->tfingers.at(i).type == FINGERDOWN)
			resumeButton.press();
		resumeButton.state = 1;
	}
	else resumeButton.state = 0;

	if(settingButton.isPressed()){
		settingScreen.addFirst(new SettingScreen(window,textureCollection,soundCollection));
		settingButton.reset();
	}
}

void PauseScreen::display()
{
	

	for (Node<SettingScreen*>*iter = settingScreen.getFirstNode(); iter != settingScreen.tail; iter = iter->next)
	{
		iter->data->display();
		if (iter->data->back()) {
			delete iter->data;
			iter->data = NULL;
			iter = settingScreen.delNode(iter);
		}	
		return;
	}

	background->setAlpha(100);
	background->setColor(255, 255, 255);
	background->render((int)(position.x), (int)position.y,
		(int)cameraSize->w, (int)cameraSize->h,0);
	background->setAlpha(255);

	if (position.x < 0) {
		if (velocity.x > 5.0f)
			velocity.set(-position.x*0.1f);

		homeButton.rectangle.x += velocity.x;
		homeButton.rectangle.y += velocity.y;

		resumeButton.rectangle.x += velocity.x;
		resumeButton.rectangle.y += velocity.y;

		settingButton.rectangle.x += velocity.x;
		settingButton.rectangle.y += velocity.y;
		position.add(velocity);
	}

	homeButton.display();
	resumeButton.display();
	settingButton.display();
}

bool PauseScreen::selected() const
{
	return (homeButton.isPressed()||resumeButton.isPressed());
}

bool PauseScreen::resume()const
{
	return resumeButton.isPressed();
}

bool PauseScreen::backHome()const
{
	return homeButton.isPressed();
}

bool PauseScreen::setting()const
{
	return settingButton.isPressed();
}
