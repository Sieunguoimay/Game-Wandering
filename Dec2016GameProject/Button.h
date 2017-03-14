#ifndef BUTTON_H
#define BUTTON_H
#include"globalheader.h"
#include"Sound.h"
#include"Texture.h"
class ButtonOnePress{
public:
	ButtonOnePress(float x,float y,float w,float h,Sound*sound,Sound*sound2,Texture*texture,bool disable = false)
	:sound(sound),texture(texture),disable(disable),sound2(sound2)
	{
		rectangle.set(x,y,w,h);
		pressed = false;
		state = 0;
		delayTime = 0.0f;
		switcher = false;
	}
	~ButtonOnePress(){
		rectangle.set(0,0,0,0);
		switcher =false;
		pressed=false;
		delayTime = 0.0f;
		state = 0;	
	}
	void display(){
		switcher = false;
		Size size(rectangle.w,rectangle.h);
		if(pressed){			
			if(delayTime == 0.0f)
				sound->play();
			if(delayTime<0.5f){
				delayTime+=1.0f/FPS;
			}else{
				pressed = false;
				state = 0;
				delayTime = 0.0f;	
				switcher = true;
				state = 0;
			}
			size.set(rectangle.w*0.95f,rectangle.h*0.95f);
		}
		texture->render(
			(int)(rectangle.x - size.w*0.5f),
			(int)(rectangle.y - size.h*0.5f),
			(int)size.w,(int)size.h,(disable?3:state));
		if (state == 1)
		{
			if (!hover)
			{
				hover = true;
				sound2->play();
			}
		}
		else if(state == 0)
			hover = false;
		
	}
	
	void press(){
		if(!disable){
			pressed = true;
			state = 1;		
		}
	}
	
	bool isPressed()const{
		return switcher;
	}
	void reset(){
		switcher = false;
	}
	bool checkInside(float x, float y){
		if(x<rectangle.x - rectangle.w/2)
		return false;
		if(x>rectangle.x+rectangle.w/2)
		return false;
		if(y<rectangle.y - rectangle.h/2)
		return false;
		if(y>rectangle.y+rectangle.h/2)
		return false;
		return true;
	}
	Rectangle getRectangle(){
		return rectangle;
	}
	Size*getTextureSize(){
		return texture->getSize();
	}
	
	Rectangle rectangle;
	int state;
private:
	bool disable;
	Texture*texture;
	Sound*sound;
	Sound*sound2;//hover sound
	bool hover;
	bool switcher;
	bool pressed;
	float delayTime;
};
class ButtonControl{

public:
	ButtonControl(float x,float y,float w,float h,Texture*texture)
		:texture(texture)
	{
		rectangle.set(x,y,w,h);
		state = 0;
		pressed = false	;
	}
	~ButtonControl(){
		
		rectangle.set(0,0,0,0);
		state = 0;
		pressed = false;
		texture= NULL;
	}
	void press(){
		pressed = true;
		state = 1;
	}
	void depress(){
		pressed = false;
		state = 0;
	}
	bool isPressed()const{
		return pressed;
	}
	
	void display(){
		Size size(rectangle.w,rectangle.h);
		if(pressed)
			size.set(rectangle.w*0.95f,rectangle.h*0.95f);
		texture->render(
			(int)(rectangle.x - size.w*0.5f),
			(int)(rectangle.y - size.h*0.5f),
			(int)size.w,(int)size.h,state);
	}
	
	bool checkInside(float x, float y){
		if(x<rectangle.x - rectangle.w/2)
		return false;
		if(x>rectangle.x+rectangle.w/2)
		return false;
		if(y<rectangle.y - rectangle.h/2)
		return false;
		if(y>rectangle.y+rectangle.h/2)
		return false;
		return true;
	}
	
	Size*getTextureSize(){
		return texture->getSize();
	}
	Rectangle getRectangle(){
		return rectangle;
	}
	Rectangle rectangle;
private:
	Texture*texture;
	bool pressed;
	int state;
};
#endif //BUTTON_H
