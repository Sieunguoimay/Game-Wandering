#include"MainManager.h"

MainManager::MainManager(){
	setup();
	loop();
}

MainManager::~MainManager(){
	
	delete touchManager;
	touchManager = NULL;

	delete clock;
	clock = NULL;
	delete mainGame;
	mainGame = NULL;
	delete window;
	window = NULL;
	delete world;
	world = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}


void MainManager::setup(){
	//INitialize system
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(20);
	
	//SDL_DisplayMode displayMode;
	//if(SDL_GetCurrentDisplayMode(0,&displayMode)==0)
		window = new Window("Game Wandering",new Size(1366,768),&renderer);
	//else return;
	window->setFullScreen(true);
	SDL_ShowCursor(SDL_DISABLE);
	world = new b2World(b2Vec2(0.0f,GRAVITY));
	clock = new Clock(FPS);
	
	mainGame = new MainGame(window,&renderer,world);
	
	touchManager=new TouchManager(4);
	contactListener = new GameContactListener();
	world->SetContactListener(contactListener);
}


void MainManager::loop(){
	SDL_Event mainEvent;
	bool runMainLoop = true;
	while(runMainLoop){
		touchManager->reset();
		while(SDL_PollEvent(&mainEvent)){
			if(mainEvent.type == SDL_QUIT)
				runMainLoop = false;
			touchManager->handleEvent(mainEvent,window->getWindowSize());
			mainGame->handleEvent(mainEvent);
		}
		mainGame->handleEvent(touchManager);
		if(mainGame->done())
			runMainLoop = false;
		SDL_SetRenderDrawColor(renderer,0xff,0x00,0xff,0xff);
		SDL_RenderClear(renderer);
		//draw everything here
		mainGame->draw();
		SDL_RenderPresent(renderer);
	
		//update worlds
		clock->work();
		world->Step(1.0f/FPS,8,3);
		contactListener->step();
	}
}
