#include "SoundController.h"



SoundController::SoundController(
	float x,float y,
	float volume,

	Texture*buttonTexture, 
	Texture*movingButtonTexture, 
	Texture*frameTexture,
	Texture*dynamicTexture,
	SoundContainer*soundCollection)
	 
	:volume(volume),dynamicTexture(dynamicTexture),position(x,y),
	
	button(x, y,
		80.0f/buttonTexture->getSize()->h*buttonTexture->getSize()->w,
		80.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		buttonTexture),
		
	frameButton(	
		x + 80.0f*2.5f, y, 
		80.0f/ frameTexture->getSize()->h*frameTexture->getSize()->w,
		80.0f,
		soundCollection->at(4),
		soundCollection->at(7),
		frameTexture),
		
	movingButton(
		x + 80.0f*2.5f 
			- 80.0f/ frameTexture->getSize()->h*frameTexture->getSize()->w*0.5f
			+ 80.0f*1.5f / movingButtonTexture->getSize()->h*movingButtonTexture->getSize()->w*0.5f
			+ UtilityFunctions::map(volume,0,SDL_MIX_MAXVOLUME, 0, 
				80.0f/ frameTexture->getSize()->h*frameTexture->getSize()->w
		 	- 80.0f*1.5f / movingButtonTexture->getSize()->h*movingButtonTexture->getSize()->w),
		
		y,
		
		80.0f*1.5f / movingButtonTexture->getSize()->h*movingButtonTexture->getSize()->w,
		80.0f*1.5f,
		movingButtonTexture)

{
	sound = soundCollection->at(4);
}


SoundController::~SoundController()
{
	dynamicTexture = NULL;
}

void SoundController::handleEvent(TouchManager*touchManager)
{

	static float head = 
		frameButton.rectangle.x 
		- frameButton.rectangle.w*0.5f 
		+ movingButton.rectangle.w*0.5f;
	static float tail = head + frameButton.getRectangle().w -
						 movingButton.getRectangle().w;

	//handle Finger Events
	movingButton.depress();
			
	for(int i =0; i<4; i++){
		if(touchManager->tfingers.at(i).type == FINGERDOWN){
			//button
			if(button.checkInside(touchManager->tfingers.at(i).x,touchManager->tfingers.at(i).y))
				button.press();
			
			//frame button
			if(frameButton.checkInside(touchManager->tfingers.at(i).x,touchManager->tfingers.at(i).y)){
				if (touchManager->tfingers.at(i).x>head&&
					touchManager->tfingers.at(i).x<tail)
				{
					movingButton.rectangle.x = touchManager->tfingers.at(i).x;
					volume = UtilityFunctions::map(
						movingButton.rectangle.x - head,
						0, tail - head,
						0, SDL_MIX_MAXVOLUME);
						
					sound->play(15);					
				}
				
			}
		}
		if(touchManager->tfingers.at(i).touching){
			
			if(movingButton.checkInside(touchManager->tfingers.at(i).x,touchManager->tfingers.at(i).y)){
				movingButton.press();
			}
			
			//moving butto
			if (movingButton.isPressed()) {
				if (touchManager->tfingers.at(i).x <= head)
				{
					sound->play();
					movingButton.rectangle.x = head;
				}
				else if (touchManager->tfingers.at(i).x >= tail)
				{
						sound->play(15);
						movingButton.rectangle.x = tail;
				}
				else 
					movingButton.rectangle.x = touchManager->tfingers.at(i).x;
				
				volume = UtilityFunctions::map(
					movingButton.rectangle.x - head,
					0, tail - head,
					0,SDL_MIX_MAXVOLUME);
			}
		}
	
	}
		
}

void SoundController::display()
{

	//dupdate and isplay
	dynamicTexture->setColor(255, 150, 0);
	dynamicTexture->render(
		(int)(frameButton.rectangle.x - frameButton.rectangle.w *0.5f
			+ movingButton.rectangle.w *0.5f),
		(int)(frameButton.rectangle.y - frameButton.rectangle.h*0.25f),
		(int)UtilityFunctions::map(volume,
			0, SDL_MIX_MAXVOLUME, 
			0, frameButton.rectangle.w - movingButton.rectangle.w),
		(int)(frameButton.rectangle.h*0.5f), 0);
	dynamicTexture->setColor(0xff,0xff,0xff);
	
	frameButton.display();
	button.display();
	movingButton.display();

}


float SoundController::getVolume() const
{
	return volume;
}

