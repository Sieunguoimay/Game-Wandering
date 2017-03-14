#pragma once
#ifndef TOUCH_MANAGER_H
#define TOUCH_MANAGER_H
#include "globalheader.h"
#define FINGERDOWN 1
#define FINGERUP 2
#define HOVER 3
struct TFingerEvent{
	TFingerEvent(){
		type = 0;
		x = 0.0f;
		y = 0.0f;
		touching = false;
	} 
	void set(float x, float y, int type){
		this->x = x;
		this->y = y;
		this->type = type;
	}
	int type;
	float x;
	float y;
	bool touching;
};
class TouchManager{
public:
	TouchManager(int maxTouchNumber)
	{
		for(int i = 0; i<maxTouchNumber; i++)
			tfingers.push_back(TFingerEvent());
	}
	~TouchManager(){
	}
	void handleEvent(SDL_Event&mainEvent,Size*windowSize){
		int ID = 0;
		if (mainEvent.type == SDL_FINGERDOWN|| mainEvent.type == SDL_FINGERMOTION) {
			ID = (int)mainEvent.tfinger.fingerId;
			if (ID < 4) {
				tfingers.at(ID).set((float)mainEvent.tfinger.x*windowSize->w,(float)mainEvent.tfinger.y*windowSize->h,FINGERDOWN);
				tfingers.at(ID).touching = true;
			}
		}
		if (mainEvent.type == SDL_FINGERUP) {
			ID = (int)mainEvent.tfinger.fingerId;
			if (ID < 4) {
				tfingers.at(ID).set(mainEvent.tfinger.x*windowSize->w,mainEvent.tfinger.y*windowSize->h,FINGERUP);
				tfingers.at(ID).touching = false;
			}
		}
		if(mainEvent.type == SDL_MOUSEMOTION)
			tfingers.at(ID).set((float)mainEvent.motion.x,(float) mainEvent.motion.y,HOVER);
		if (mainEvent.type == SDL_MOUSEBUTTONDOWN) {
			ID = 0;
			tfingers.at(ID).set((float)mainEvent.motion.x, (float)mainEvent.motion.y, FINGERDOWN);
			tfingers.at(ID).touching = true;
		}
		if (mainEvent.type == SDL_MOUSEBUTTONUP) {
			ID = 0;
			if (ID < 4) {
				tfingers.at(ID).set((float)mainEvent.motion.x, (float)mainEvent.motion.y, FINGERUP);
				tfingers.at(ID).touching = false;
			}
		}
	}
	void reset(){
		for(size_t i = 0; i<tfingers.size();i++){
			tfingers.at(i).type = 0;;
		
		}
	}
	std::vector<TFingerEvent>tfingers;
};
#endif //TOUCH_MANAGER_H
