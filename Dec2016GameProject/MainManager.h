#pragma once
#ifndef MAIN_MANAGER_H
#define MAIN_MANAGER_H
#include"globalheader.h"
#include"Window.h"
#include"MainGame.h"
#include"Clock.h"
#include"TouchManager.h"
#include"GameContactListener.h"
class MainManager{
	public:
		MainManager();
		~MainManager();		
	private:
		void setup();
		void loop();
		Window*window;
		SDL_Renderer*renderer;
		b2World*world;
		Clock*clock;
		MainGame*mainGame;
		TouchManager*touchManager;
		GameContactListener*contactListener;
};
#endif //MAIN_MANAGER_H
