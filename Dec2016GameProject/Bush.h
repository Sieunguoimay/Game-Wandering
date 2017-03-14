#ifndef BUSH_H
#define BUSH_H
#include"Texture.h"
#include"Camera.h"
#include"globalheader.h"
class Bush{
public:
	Bush(float x,float y,float w,float h,int index,Texture*texture)
	:position(x,y),size(w,h),texture(texture),index(index)
	{}
	~Bush(){
		texture =  NULL;
	}
	void display(const Camera&camera){
		texture->render(camera,position.x-size.w*0.5f-camera.getPosition().x,
			position.y-size.h-camera.getPosition().y,size.w,size.h,index);
	}
	Vector2D position;
private:
	int index;
	Size size;
	Texture*texture;
};

class Bushes{
	public:
		Bushes(std::vector<Texture*>*textureCollection)
			:textureCollection(textureCollection)
		{
		}
		~Bushes(){
			textureCollection = NULL;
			for(Node<Bush*>*iter = bushes.getFirstNode();iter!=bushes.tail;iter = iter->next){
				delete iter->data;
				iter->data = NULL;
			}
		}
		void display(const Camera&camera){
			for(Node<Bush*>*iter = bushes.getFirstNode();iter!=bushes.tail;iter = iter->next){
				iter->data->display(camera);
			}
		}
		void addNew(float x,float y,int index,bool leftOrRight){
			for(Node<Bush*>*iter = bushes.getFirstNode();iter!=bushes.tail;iter = iter->next)
				if(iter->data->position.x==x)
					return;
			if(leftOrRight)
			{
				if(index==4)	
					bushes.addFirst(new Bush(x,y,300.0f,500.0f,0,textureCollection->at(4)));
				else 
					bushes.addFirst(new Bush(x,y,200.0f,100.0f,index,textureCollection->at(1)));
			}else{
				if(index==4)	
					bushes.addLast(new Bush(x,y,300.0f,500.0f,0,textureCollection->at(4)));
				else 
					bushes.addLast(new Bush(x,y,200.0f,100.0f,index,textureCollection->at(1)));
			}
		}
		void del(bool leftOrRight){
					
			if (leftOrRight) {
				delete bushes.getFirstNode()->data;
				bushes.getFirstNode()->data = NULL;
				bushes.delFist();//right
			}
			else {
				delete bushes.tail->prev->data;
				bushes.tail->prev->data = NULL;
				bushes.delLast();//left	
			}
		}
	private:
		LinkedList<Bush*>bushes;
		std::vector<Texture*>*textureCollection;
};
#endif//BUSH_H
