#include"MainManager.h"
int main(int argc,char*args[]){
	MainManager*mainManager = new MainManager();
	delete mainManager;
	mainManager = NULL;
	return 0;
}
