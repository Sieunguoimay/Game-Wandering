#include"LevelManager.h"

LevelManager::LevelManager(Map*map,SoundContainer*soundCollection,std::vector<Texture*>*textureCollection)
:map(map),sound(soundCollection->at(6)),texture(textureCollection->at(36))
,soundCollection(soundCollection),textureCollection(textureCollection)
{
	
	cleared = false;
	soundPlayed = false;
	reachedDestination = false;
	isItTimeToReset = false;
}
LevelManager::~LevelManager(){
	map = NULL;
	sound = NULL;
	texture= NULL;
	
	cleared = false;
	soundPlayed = false;
	reachedDestination = false;
	isItTimeToReset = false;
	for(Node<YouWin*>*iter=youWin.getFirstNode(); iter!= youWin.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	textureCollection = NULL;
	soundCollection = NULL;
}
void LevelManager::display(const Camera&camera){
	if (reachedDestination) {
		
		for(Node<YouWin*>*iter = youWin.getFirstNode(); iter != youWin.tail; iter = iter->next)
		{
			iter->data->display(camera);
			if(iter->data->done()){
				delete iter->data;
				iter->data = NULL;
				cleared = true;
				iter = youWin.delNode(iter);
			}
			return;
		}
		
		
		if (!soundPlayed) {
			sound->play();
			soundPlayed = true;
		}
		//delay for 1.5second
		static const float TIMEDELAY = 2.5;
		static float timeCounter = TIMEDELAY;
		timeCounter -= 1.0f / FPS;
		//after that
		if (timeCounter <= 0)
		{
			timeCounter = TIMEDELAY;//set it again incase nexttime it will be 0

			if (map->getCurrentMapLevel() == 3)
			{
				youWin.addFirst(new YouWin(textureCollection,soundCollection));
				return;
			}
			map->next();
			isItTimeToReset = true;
		}else
		texture->setAlpha((int32)(((TIMEDELAY - timeCounter) / TIMEDELAY) * 255.0f));
		texture->setColor(0xff,0xff,0xff);
		int x = 0;
		texture->render(x, x, (int)camera.getSize().w , (int)camera.getSize().h,0);
		texture->setAlpha(255);
	}
}
void LevelManager::setNextLevel(){
	reachedDestination = true;
}
