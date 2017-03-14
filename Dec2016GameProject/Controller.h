#ifndef CONTROLLER_H
#define CONTROLLER_H
#include"globalheader.h"
#include"Button.h"
#include"TouchManager.h"
#include"Mover.h"
class Controller {
public:
	Controller(Size*windowSize, std::vector<Texture*>*textureCollection, SoundContainer*soundCollection, Mover*mover)
		:mover(mover)
	{

		float y = windowSize->h - windowSize->w / 12.0f;
		float w = windowSize->w / 12.0f;
		float h = w;

		buttons.push_back(new ButtonControl(windowSize->w / 13.0f, y - w, w, h, textureCollection->at(43)));
		//jump
		buttons.push_back(new ButtonControl(windowSize->w*13.0f / 14.0f - w*1.5f, y, w, h, textureCollection->at(45)));

		buttons.push_back(new ButtonControl(windowSize->w / 13.0f + 1.5f*w, y, w, h, textureCollection->at(44)));
		//fire
		buttons.push_back(new ButtonControl(windowSize->w*13.0f / 14.0f, y - w, w, h, textureCollection->at(46)));//fire


		//exit button
		homeButton = new ButtonOnePress(
			windowSize->w / 14.0f, windowSize->h - y,
			w*0.75f, h*0.75f, soundCollection->at(4),
			soundCollection->at(7),
			textureCollection->at(51));
	}
	~Controller() {
		delete homeButton;
		homeButton = NULL;
		for (size_t i = 0; i < buttons.size(); i++) {
			delete buttons.at(i);
			buttons.at(i) = NULL;
		}
		mover = NULL;
	}
	void handleEvent(TouchManager*touchManager) {
		
		for (size_t i = 0; i < buttons.size(); i++)
			buttons.at(i)->depress();

		for (int i = 0; i < 4; i++) {

			if (touchManager->tfingers.at(i).touching)
				for (size_t j = 0; j < buttons.size(); j++) {
					if (buttons.at(j)->checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
					{
						buttons.at(j)->press();
					}
				}
			if (touchManager->tfingers.at(i).type == FINGERDOWN)
				if (homeButton->checkInside(touchManager->tfingers.at(i).x, touchManager->tfingers.at(i).y))
					homeButton->press();
		}
	}
	void handleEvent(SDL_Event&mainEvent)
	{
		mover->handleEvent(mainEvent);

	}
		bool done()const{
			return (homeButton->isPressed());
		}
		void display(){

			for(size_t i = 0; i<buttons.size(); i++){
					buttons.at(i)->display();
			}
			homeButton->display();
		}
		
		ButtonOnePress*homeButton;
	private:
		std::vector<ButtonControl*>buttons;
		Mover*mover;
};

#endif //CONTROLLER_H
