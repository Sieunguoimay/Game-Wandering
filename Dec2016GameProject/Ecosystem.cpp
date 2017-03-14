#include"Ecosystem.h"

Ecosystem::Ecosystem(b2World*world,Mover*mover,Map*map,LevelManager*levelManager,
	std::vector<Texture*>*textureCollection,
	SoundContainer*soundCollection)
	:map(map),
	textureCollection(textureCollection),
	soundCollection(soundCollection)
	,ground(world,textureCollection->at(0))
	,monsters(world,mover,textureCollection,soundCollection)
	,clouds(world,textureCollection,soundCollection)
	,poles(world,mover,textureCollection,soundCollection)
	,bridges(world,textureCollection)
	,pools(world,textureCollection)
	,gears(world,textureCollection)
	,emitters(world,textureCollection,soundCollection)
	,reflectors(world,textureCollection->at(7))
	,destinations(world,levelManager,textureCollection)
	,bushes(textureCollection)
{
	putEverythingAtFirst();
}
Ecosystem::~Ecosystem(){
	map = NULL;
	textureCollection = NULL;
	soundCollection = NULL;
}
void Ecosystem::display(const Camera&camera){
	updateLandscape(camera.getPosition().x);
	clouds.display(camera);
	ground.display(camera);
	bushes.display(camera);
	monsters.display(camera);
	poles.display(camera);
	emitters.display(camera);
	reflectors.display(camera);
	destinations.display(camera);
}
void Ecosystem::display2(const Camera&camera){
	bridges.display(camera);
	pools.display(camera);
	gears.display(camera);
}

void Ecosystem::putEverything(float x, float y, char ID, bool leftOrRight){
	if (ID == '0')
		ground.putNewBrick(x, y, 0, leftOrRight);
	else if (ID == '1')
		ground.putNewBrick(x, y, 1, leftOrRight);
	else if (ID == '2')
		ground.putNewBrick(x, y, 2, leftOrRight);
	else if(ID>='3'&&ID<='7')
		bushes.addNew(x,y-ground.getSize().h*0.5f,UtilityFunctions::charToInt(ID) -3,leftOrRight);
	else if(ID == '8')
		monsters.addNew(x,y);
	else if(ID=='9')
		emitters.addNew(x,y);
	else if (ID == 'a'|| ID == 'b'|| ID == 'c'|| ID == 'd')
		reflectors.addNew(x, y, (int)ID,leftOrRight);
	

	else if(ID=='e')
		poles.addNew(x,y+ground.getSize().h*0.5f,leftOrRight);
		
	else if(ID=='f')
		bridges.addNew(x,y);
		
	else if(ID=='i')
		clouds.addNew(x,y);
	
	else if(ID=='j')
		clouds.addNewDark(x,y);
		
	else if(ID=='f')
		bridges.addNew(x,y);
		
	else if(ID=='g')
		pools.addNew(x,y,ground.getSize().w,0);
		
	else if(ID=='h')
		pools.addNew(x,y,ground.getSize().w,1);
	else if(ID=='o')
		pools.addNew(x,y,ground.getSize().w,2);
		
	else if(ID=='k')
		gears.addNew(x,y+ground.getSize().h,1);
	else if(ID=='l')
		gears.addNew(x,y+ground.getSize().h,2);
	else if(ID=='m')
		gears.addNew(x,y+ground.getSize().h,3);
	else if(ID=='n')
		destinations.addNew(x,y+ground.getSize().h*0.5f,leftOrRight);
}

void Ecosystem::delEverything(char ID,bool leftOrRight){
	if (ID == '0'||ID == '1'||ID == '2')
		ground.delBrick(leftOrRight);
	else if(ID>='3'&&ID<='7')
		bushes.del(leftOrRight);
	else if (ID=='e')
		poles.del(leftOrRight);
	else if (ID == 'a'|| ID == 'b'|| ID == 'c'|| ID == 'd') 
		reflectors.del(leftOrRight);
	else if(ID=='n')
		destinations.del(leftOrRight);
}





void Ecosystem::updateLandscape(float cameraPosX){
	float x = 0.0f;
	float y = 0.0f;
	int numberBrickAdded =0;
	float a = (map->getFirstIndex()+map->getNumberBricks()/3+1)*ground.getSize().w;
	float b =(map->getFirstIndex() + map->getNumberBricks() / 3)*ground.getSize().w;
	
	if(cameraPosX > a&&(map->getLastIndex()<map->getSize())){
		for (size_t i = 0; i < map->getMapDataOnTheRight()->size(); i++){
			char ID = map->getMapDataOnTheRight()->at(i);
			if(ID>='0'){
				
				x = (float)map->getLastIndex()*ground.getSize().w;
				if (!(ID == '0' || ID == '1' || ID == '2'))
					numberBrickAdded--;
				if (conditionToPutBush(ID)) {
					float y = (15.0f - (float)numberBrickAdded)*ground.getSize().h;
					putEverything(x, y, ID, true);
				}
				else {//group 1: reflector...
					float y = (15.0f - (float)i)*ground.getSize().h;
					putEverything(x, y, ID, true);
				}
			}
			numberBrickAdded++;
		}
		
		
		
		for (size_t i = 0; i < map->getMapDataOnTheLeft()->size(); i++){
			if (map->getMapDataOnTheLeft()->at(i) >= '0'){
				char ID = map->getMapDataOnTheLeft()->at(i);
				delEverything(ID,false);
			}
		}
		map->increaseIndex();
	}else if(cameraPosX < b&& map->getFirstIndex()>0){
		map->decreaseIndex();
		for (size_t i = 0; i < map->getMapDataOnTheLeft()->size(); i++){
			char ID = map->getMapDataOnTheLeft()->at(i);
			if(ID>='0'){
				
				x = (float)map->getFirstIndex()*ground.getSize().w;
		
				if (!(ID == '0' || ID == '1' || ID == '2'))
					numberBrickAdded--;
		
				if (conditionToPutBush(ID)) {
					float y = (15.0f - (float)numberBrickAdded)*ground.getSize().h;
					putEverything(x, y, ID, false);
				}
				else {//group 1: reflector...
					float y = (15.0f - (float)i)*ground.getSize().h;
					putEverything(x, y, ID, false);
				}
			}
			numberBrickAdded++;
		}
	
		for (size_t i = 0; i < map->getMapDataOnTheRight()->size(); i++){
			if (map->getMapDataOnTheRight()->at(i) >= '0'){
				char ID = map->getMapDataOnTheRight()->at(i);
				delEverything(ID, true);
			}
		}	
	}
}


void Ecosystem::putEverythingAtFirst(){
	for(int i = 0; i<map->getNumberBricks();i++){
		int numberBrickAdded = 0;
		for(size_t j = 0; j<map->getMapData(i)->size();j++){
			char ID = map->getMapData(i)->at(j);
			if(ID>='0') {
				
				float x = (float)i*ground.getSize().w;
				if (!(ID == '0' || ID == '1' || ID == '2'))
					numberBrickAdded--;
					
				if (conditionToPutBush(ID)) {
					float y = (15.0f - (float)numberBrickAdded)*ground.getSize().h;
					putEverything(x, y, ID, true);
				}
				else {
					float y = (15.0f - (float)j)*ground.getSize().h;
					putEverything(x, y, ID, true);
				}
			}
			numberBrickAdded++;
		}
	}
}

bool Ecosystem::conditionToPutBush(char & ID)
{
	return (ID == '3' || ID == '4' || ID == '5' || ID == '6' || ID == '7');
}
