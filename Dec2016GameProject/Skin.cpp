#include "Skin.h"



Skin::Skin(Texture*bodyTexture,Texture*legsTexture,Texture*eyeTexture,
	Size * size,Vector2D * position)
:bodyTexture(bodyTexture),legsTexture(legsTexture),eyeTexture(eyeTexture),
	size(size),position(position)
{
	
	horizontalFlip = true;
	numLegSprites = 9;//I know that because I created the image

	spriteIndices.push_back(0);//0 - 9sprites
	spriteIndices.push_back(0);//1 - 4 sprites 
	//create a new integer variable store inside vector spriteIndexes
}


Skin::~Skin()
{
	eyeTexture = NULL;
	legsTexture = NULL;
	bodyTexture = NULL;
}

void Skin::render(const Camera&camera)
{
	blink();

	bodyTexture->render(camera,
		position->x - size->w*0.5f - camera.getPosition().x,
		position->y - size->h*0.5f - camera.getPosition().y,
		size->w,
		size->h,
		0, 0, horizontalFlip
	);

	eyeTexture->render(camera,
		position->x - size->w*0.5f - camera.getPosition().x,
		position->y - size->h*0.5f - camera.getPosition().y,
		size->w,
		size->h,
		spriteIndices.at(1), 0, horizontalFlip
	);

	legsTexture->render(camera,
		position->x - size->w*0.5f - camera.getPosition().x,
		position->y - size->h*0.5f - camera.getPosition().y,
		size->w,
		size->h,
		spriteIndices.at(0),
		 0, horizontalFlip
	);
}

void Skin::walk(float velocityX)
{
	
	if (velocityX > 0.001f) {
		horizontalFlip = true;
	}
	else if (velocityX < -0.001f) { 
		horizontalFlip = false; 
	}
	//else it remain the same

	float framePerSecond = 10.0f*(velocityX>0?velocityX:-velocityX);
	static int signOfIndex = 1;
	secondPerLoop += 1.0f / FPS;

	if (secondPerLoop > (1.0f / framePerSecond)) {
		//Legs sprites update
		spriteIndices.at(0)+=signOfIndex;//+ or - to 1
		if (spriteIndices.at(0) == 0 ||
			spriteIndices.at(0) == numLegSprites - 1)
			signOfIndex *= -1;
		secondPerLoop = 0.0f;
	}
}
void Skin::blink()
{
	static bool blinked = false;
	static float duration = 0;
	duration -= 1.0f / FPS;
	if (duration <= 0.0f) {
		blinked = true;
		duration = (float)(rand() % 5 + 1);
	}

	if (blinked) {
		static float seconds = 0.0f;
		seconds += 1.0f / FPS;

		float fps = 10;
		if (seconds > 1.0f / fps) {
			if (spriteIndices.at(1) <= 0) {
				spriteIndices.at(1) = 4;
			}
			spriteIndices.at(1)--;
			seconds = 0.0f;
			if (spriteIndices.at(1) == 0)
				blinked = false;
		}
	}
}
