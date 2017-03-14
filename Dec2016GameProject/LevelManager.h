#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include"Map.h"
#include"Texture.h"
#include"Camera.h"
#include"SoundContainer.h"
#include"YouWin.h"
class LevelManager{
public:
	LevelManager(Map*map,SoundContainer*soundCollection,
		std::vector<Texture*>*textureCollection);
	~LevelManager();
	void display(const Camera&camera);
	void setNextLevel();
	bool isCleared()const{
		return cleared;
	}
	bool resetSystemNow()const{
		return isItTimeToReset;
	}
private:
	LinkedList<YouWin*> youWin;
	SoundContainer*soundCollection;
	std::vector<Texture*>*textureCollection;
	bool isItTimeToReset;
	bool reachedDestination;
	bool soundPlayed;
	bool cleared;
	Map*map;
	Texture*texture;
	Sound*sound;
};

#endif//LEVELMANAGER_H
