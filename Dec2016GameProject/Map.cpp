#include "Map.h"



Map::Map()
{
	setup();
	
}


Map::~Map()
{
	for (int i = 0; i<4;i++)
		for (size_t j = 0; j < maps[i].size(); j++)
			maps[i].at(j) = NULL;
	for(size_t i = 0; i<mapStore->size();i++)
	{
		delete mapStore->at(i);
		mapStore->at(i) = NULL;
	}
	delete mapStore;
	mapStore = NULL;
}	

void Map::setup()
{
	maxSavedMapLevel = loadCurrentMapIndex();
	firstIndex = 0;
	numberBrickBeingDisplayed = 50;
	currentMapLevel = 0;


	mapStore = loadDataFromFile("map.txt");

	divideMap(0,153,maps[0]);
	
	divideMap(152,329,maps[1]);
	
	divideMap(329,525,maps[2]);
	
	divideMap(525,mapStore->size(),maps[3]);
}

void Map::reset()
{
	firstIndex = 0;
	numberBrickBeingDisplayed = 50;
}

int Map::getSize() const
{
	return maps[currentMapLevel].size();
}

std::vector<char>* Map::getMapData(const int index)
{
	// TODO: insert return statement here
	return maps[currentMapLevel].at(index);
}

std::vector<char>* Map::getMapDataOnTheRight()
{
	return getMapData( firstIndex+numberBrickBeingDisplayed);
}

std::vector<char>* Map::getMapDataOnTheLeft()
{
	return getMapData(firstIndex);
}


int Map::getFirstIndex() const
{
	return this->firstIndex;
}

int Map::getLastIndex()
{
	return firstIndex+numberBrickBeingDisplayed;
}


int Map::getNumberBricks() const
{
	return this->numberBrickBeingDisplayed;
}

void Map::increaseIndex()
{
	firstIndex++;
}

void Map::decreaseIndex()
{
	firstIndex--;
}

int Map::next()
{
	if(currentMapLevel<3)
	{
		currentMapLevel++;
		if (currentMapLevel > maxSavedMapLevel)
			maxSavedMapLevel = currentMapLevel;
	}
	return currentMapLevel;
}

void Map::setMapLevel(int index)
{
	if(currentMapLevel<4)
		currentMapLevel = index;
	
}

int Map::getMapLevelSaved()
{
	return maxSavedMapLevel;
}

int Map::getCurrentMapLevel() const
{
	return currentMapLevel;
}

void Map::writeCurrentMapIndexToFile()
{
	std::string path = 
		//SDL_AndroidGetExternalStoragePath();
	//path = path+
		"data.txt";
	SDL_RWops*file = SDL_RWFromFile(path.c_str(), "wb");
	char c = (maxSavedMapLevel+'0');
	if (file != NULL) {	
		SDL_RWwrite(file, &c,sizeof(c) , 1);
		file->close(file);
	}
}

int Map::loadCurrentMapIndex()
{
	
	std::string path = "data.txt";

	SDL_RWops *file = SDL_RWFromFile(path.c_str(), "rb");
	char c = '0';

	if(file!=NULL){	
		SDL_RWread(file, &c,sizeof(c) , 1);
		file->close(file);
	}
	int a = c-'0';
	return a;
}

std::vector<std::vector<char>*>*Map::loadDataFromFile(std::string path)
{
	std::vector<std::vector<char>*>*tempData = new std::vector<std::vector<char>*>();
	std::vector<char>*temp = new std::vector<char>();
	char iterator;
	//int type;
	std::string path2 = 
		//SDL_AndroidGetInternalStoragePath()+'/'+
		path;
	SDL_RWops*file = SDL_RWFromFile(path2.c_str(), "rb");

	if (file != NULL) {
		while (file->read(file, &iterator, sizeof(iterator), 1) > 0) {
			if (iterator == '.')
				break;//completed.
			if (iterator == '\n') {
				tempData->push_back(temp);
				temp = new std::vector<char>();
			}
			else{
				temp->push_back(iterator);
			}
		}
		file->close(file);
	}
	delete temp;
	temp = NULL;
	return tempData;
}

void Map::divideMap(int begin,int end,Matrix&matrix){
	for(int i = begin; i<end;i++)
		matrix.push_back(mapStore->at(i));
}
