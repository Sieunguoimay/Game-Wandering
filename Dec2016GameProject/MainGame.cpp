#include"MainGame.h"
MainGame::MainGame(Window*window,SDL_Renderer**renderer,b2World*world)
:windowSize(window->getWindowSize()),window(window),renderer(renderer),world(world)
{
	loadAssets();
	setup();
}
MainGame::~MainGame(){
	window = NULL;
	delete mover;
	mover = NULL;
	delete ecosystem;
	ecosystem=NULL;
	delete background;
	background = NULL;
	windowSize = NULL;
	renderer = NULL;
	for(size_t i =  0; i<textureCollection->size(); i++)
	{
		delete textureCollection->at(i);
		textureCollection->at(i) = NULL;
	}
	delete textureCollection;
	textureCollection = NULL;
	delete soundCollection;
	soundCollection = NULL;
	
	delete levelManager;
	levelManager = NULL;
	delete map;
	map = NULL;
	world = NULL;
	delete camera;
	camera = NULL;
	delete mouse;
	mouse = NULL;
}

void MainGame::setup(){
	
	levelManager = new LevelManager(map,soundCollection,textureCollection);
	
	mover = new Mover(world,textureCollection,soundCollection);
	ecosystem = new Ecosystem(world,mover,map,levelManager,textureCollection,soundCollection);	
	controller = new Controller(windowSize,textureCollection,soundCollection,mover);
	camera = new Camera(windowSize);
	background = new Background();
	background->setup(textureCollection);
	home();
	poster.addFirst(new Poster(windowSize,
		textureCollection->at(34),
		textureCollection->at(35),
		soundCollection));
	mouse = new Mouse(textureCollection->at(25));
}

void MainGame::handleEvent(SDL_Event & mainEvent)
{
	controller->handleEvent(mainEvent);
	if (mainEvent.type == SDL_KEYDOWN) {
		if (mainEvent.key.keysym.sym == SDLK_ESCAPE)
		{
			pause.addFirst(new PauseScreen(window, textureCollection, soundCollection));
			controller->homeButton->reset();
		}
		if (!poster.isEmpty())
			poster.getFirstNode()->data->up();
	}
}

void MainGame::handleEvent(TouchManager*touchManager){
	
	mouse->handleEvent(touchManager);
	for(Node<Poster*>*iter = poster.getFirstNode();iter!=poster.tail;iter=iter->next){
		iter->data->handleEvent(touchManager);
		return;	
	}
	for(Node<MenuManager*>*iter = menu.getFirstNode(); iter!=menu.tail; iter=iter->next){
		iter->data->handleEvent(touchManager);
		return;
	}
	
	for(Node<PauseScreen*>*iter = pause.getFirstNode(); iter!=pause.tail; iter=iter->next){
		iter->data->handleEvent(touchManager);
		return;
	}
/*	controller->handleEvent(touchManager);
	if(controller->done()){
		pause.addFirst(new PauseScreen(windowSize,textureCollection,soundCollection));
		controller->homeButton->reset();
	}*/
}


void MainGame::draw(){

	for(Node<MenuManager*>*iter = menu.getFirstNode(); iter!=menu.tail; iter=iter->next){
		
		iter->data->display();
		if(iter->data->hasSelected()){
			delete iter->data;
			iter->data = NULL;
			iter = menu.delNode(iter);
			reset();
		}
			
		for(Node<Poster*>*iter = poster.getFirstNode();iter!=poster.tail;iter=iter->next){
			iter->data->display();
			if(iter->data->hasDone()){
				delete iter->data;
				iter->data = NULL;
				iter = poster.delNode(iter);
			}
		}
		mouse->display(*camera);
		return;
	}
	
	camera->update();
	background->display(*camera);
	ecosystem->display(*camera);
	
	for(Node<PauseScreen*>*iter = pause.getFirstNode(); iter!=pause.tail; iter=iter->next){
		iter->data->display();
		if (iter->data->backHome()) 
			home();
		if(iter->data->selected()){
			delete iter->data;
			iter->data = NULL;
			iter = pause.delNode(iter);
		}
		mouse->display(*camera);
		return;
	}
	
	mover->display(*camera);
	ecosystem->display2(*camera);
	background->display2(*camera);

	//controller->display();
	levelManager->display(*camera);
	if(levelManager->isCleared())
		home();
	if(mover->hasExploded()||levelManager->resetSystemNow())
		reset();

}


void MainGame::reset(){
	soundCollection->at(5)->play();
	
	delete levelManager;
	levelManager = new LevelManager(map,
		soundCollection,textureCollection);
	
	delete ecosystem;
	ecosystem = new Ecosystem(world,mover,map,levelManager,textureCollection,soundCollection);
	
	//delete background;
	//background = new Background(map->getCurrentMapLevel(),textureCollection);
	background->reset(map->getCurrentMapLevel());
	delete camera;
	camera = new Camera(windowSize);
	
	delete controller;
	controller = new Controller(windowSize,textureCollection,soundCollection,mover);
		
	map->reset();
	mover->reset();

}
void MainGame::home(){
	menu.addLast(new MenuManager(map,
		window,textureCollection,soundCollection));
}
bool MainGame::done(){
	bool exitNow = false;
	for(Node<MenuManager*>*iter = menu.getFirstNode(); iter!=menu.tail; iter=iter->next)
		exitNow = iter->data->exitGameNow();
	//exitNow = controller->done();
	if(exitNow)
		map->writeCurrentMapIndexToFile();
	return exitNow;
}




















void MainGame::loadAssets(){
	Texture*tempTexture =new Texture("images/mainposter.png", renderer, 1);
	int x = 0;
	tempTexture->render(x,x,(int)windowSize->w,(int)windowSize->h,0);
	SDL_RenderPresent(*renderer);
	
	map = new Map();
	soundCollection = new SoundContainer();
	
	textureCollection = new std::vector<Texture*>();	
	textureCollection->push_back(new Texture("images/brick2.png", renderer, 3));
	textureCollection->push_back(new Texture("images/bushes.png", renderer, 4));
	textureCollection->push_back(new Texture("images/monster_tomato.png", renderer, 5));
	textureCollection->push_back(new Texture("images/bulb.png", renderer, 1));
	textureCollection->push_back(new Texture("images/tree.png", renderer, 1));
	textureCollection->push_back(new Texture("images/gear.png", renderer, 1));
	textureCollection->push_back(new Texture("images/stick.png", renderer, 1));
	textureCollection->push_back(new Texture("images/mirror.png", renderer, 1));
	textureCollection->push_back(new Texture("images/wood.png", renderer, 1));
	textureCollection->push_back(new Texture("images/root.png", renderer, 1));
	textureCollection->push_back(new Texture("images/laser.png", renderer, 1));//10
	textureCollection->push_back(new Texture("images/fly.png", renderer, 1));//11
	textureCollection->push_back(new Texture("images/powerpole.png", renderer, 1));//12

	textureCollection->push_back(new Texture("images/rectangle.png", renderer, 1));//13 pool
	textureCollection->push_back(new Texture("images/fish.png", renderer, 1));//14
	textureCollection->push_back(new Texture("images/floatingwood.png", renderer, 1));//15

	textureCollection->push_back(new Texture("images/cloud.png", renderer, 1));//16 - clouds
	textureCollection->push_back(new Texture("images/rectangle.png", renderer, 1));//17  rainDrop
	textureCollection->push_back(new Texture("images/rectangle.png", renderer, 1));//18  thunder lightning
	textureCollection->push_back(new Texture("images/destination.png", renderer, 1));//19  destination texture
	textureCollection->push_back(new Texture("images/rectangle.png", renderer, 1));//20  nextlevel texture


	textureCollection->push_back(new Texture("images/mapbutton.png", renderer, 4));//21 - for menu
	textureCollection->push_back(new Texture("images/levelnumber.png", renderer, NUM_MAP_LEVEL));//22 - for menu
	textureCollection->push_back(new Texture("images/backgroundmenu.png", renderer, 1));//23- for menu

	textureCollection->push_back(new Texture("images/exitbutton.png", renderer, 4));//24- for menu
	textureCollection->push_back(new Texture("images/mousecursor.png", renderer, 2));//25- for menu

	textureCollection->push_back(new Texture("images/homebutton.png", renderer, 3));//26- for menu
	textureCollection->push_back(new Texture("images/resumebutton.png", renderer, 3));//27- for menu
	textureCollection->push_back(new Texture("images/settingbutton.png", renderer, 3));//28- for menu
	
	textureCollection->push_back(new Texture("images/backbutton.png", renderer, 3));//29- for menu

	textureCollection->push_back(new Texture("images/chunkbutton.png", renderer, 4));//30- for menu
	textureCollection->push_back(new Texture("images/musicbutton.png", renderer, 4));//31- for menu
	textureCollection->push_back(new Texture("images/framesoundcontroller.png", renderer, 1));//32- for menu
	textureCollection->push_back(new Texture("images/movingbuttonsoundcontroller.png", renderer, 3));//33- for menu
	
	textureCollection->push_back(tempTexture);//34- for menu
	textureCollection->push_back(new Texture("images/pressanykey.png", renderer, 1));//35- for menu


	//background
	textureCollection->push_back(new Texture("images/rectangle.png", renderer));//36
	textureCollection->push_back(new Texture("images/background_midlayer.png", renderer));//37
	textureCollection->push_back(new Texture("images/rectangle.png", renderer));//38 mountain brick
	textureCollection->push_back(new Texture("images/foreshader.png", renderer));//39 mountain brick

	textureCollection->push_back(new Texture("images/onfullscreenbutton.png", renderer,3));//40 mountain brick
	textureCollection->push_back(new Texture("images/offfullscreenbutton.png", renderer, 3));//41 mountain brick
	textureCollection->push_back(new Texture("images/youwin.png", renderer,1));//42 mountain brick


	textureCollection->push_back(new Texture("images/leftbutton.png", renderer, 2));//43- for menu

	textureCollection->push_back(new Texture("images/rightbutton.png", renderer, 2));//44- for menu

	textureCollection->push_back(new Texture("images/jumpbutton.png", renderer, 2));//45- for menu

	textureCollection->push_back(new Texture("images/firebutton.png", renderer, 2));//46- for menu


//mover skins
	textureCollection->push_back(new Texture("images/body.png", renderer, 1));//47
	textureCollection->push_back(new Texture("images/legs.png", renderer, 9));//48
	textureCollection->push_back(new Texture("images/eye.png", renderer, 4));//49
	textureCollection->push_back(new Texture("images/bulb2.png", renderer, 1));//50

	textureCollection->push_back(new Texture("images/pausebutton.png", renderer, 2));//51


}
