#pragma once
#ifndef MAIN_GAME_H
#define MAIN_GAME_H
#include"Map.h"
#include"globalheader.h"
#include"SoundContainer.h"
#include"Texture.h"
#include"TouchManager.h"
#include"Controller.h"
#include"Camera.h"
#include"Mover.h"
#include"LevelManager.h"
#include"Poster.h"
#include"MenuManager.h"
#include"Ecosystem.h"
#include"Background.h"
#include"PauseScreen.h"
#include"Mouse.h"
class MainGame{
public:
	MainGame(Window*window,SDL_Renderer**renderer,b2World*world);
	~MainGame();
	void setup();
	void handleEvent(SDL_Event&mainEvent);
	void handleEvent(TouchManager*touchManager);
	void draw();
	bool done();
private:
	void home();
	void reset();
	void loadAssets();
	Mover*mover;
	Ecosystem*ecosystem;
	Background*background;
	//Some means
	Mouse*mouse;
	LinkedList<MenuManager*>menu;
	LinkedList<Poster*>poster;
	LinkedList<PauseScreen*>pause;
	LevelManager*levelManager;
	std::vector<Texture*>*textureCollection;
	SoundContainer*soundCollection;
	Map*map;
	Controller*controller;
	Camera*camera;
	//pointers
	Window*window;
	Size*windowSize;
	SDL_Renderer**renderer;
	b2World*world;
};
#endif //MAIN_GAME_H
