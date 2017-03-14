#pragma once
#ifndef MAP_H
#define MAP_H
#include"globalheader.h"
typedef std::vector<std::vector<char>*> Matrix;
class Map
{
public:
	Map();
	~Map();
	void setup();
	void reset();
	int getSize()const;
	std::vector<char>*getMapData(const int index);
	std::vector<char>*getMapDataOnTheRight();
	std::vector<char>*getMapDataOnTheLeft();


	int getNumberBricks()const;
	int getFirstIndex()const;
	int getLastIndex();
	void increaseIndex();
	void decreaseIndex();
	int next();
	void setMapLevel(int index);
	int getMapLevelSaved();
	int getCurrentMapLevel()const;
	void writeCurrentMapIndexToFile();

protected:
	int loadCurrentMapIndex();
	std::vector<std::vector<char>*>*loadDataFromFile(std::string path);
	void divideMap(int begin,int end,Matrix&matrix);
	//std::vector<Matrix*>mapContainer;
	
	Matrix*mapStore;
	Matrix maps[4];//1 array
	int firstIndex;

	int numberBrickBeingDisplayed;
	int currentMapLevel;
	int maxSavedMapLevel;
};

#endif // !MAP_H
