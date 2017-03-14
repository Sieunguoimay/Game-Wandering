#include "YouWin.h"



YouWin::YouWin(std::vector<Texture*>*textureCollection, SoundContainer*soundCollection)
	:textureCollection(textureCollection),soundCollection(soundCollection)
{
	timeDisplay = 20.0f;
	soundCollection->playMusicLoopForever();
}


YouWin::~YouWin()
{
	for (Node<FireWork*>*iter = fireWork.getFirstNode(); iter != fireWork.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	timeDisplay = 0.0f;
	textureCollection = NULL;
	soundCollection = NULL;
}

void YouWin::display(const Camera & camera)
{
	timeDisplay -= 1.0f / FPS;
	float frequency = 3.0f;
	static float timePerFireWork = 0;
	timePerFireWork += 1.0f / FPS;

	if (timeDisplay > 0.0f)
		if (fireWork.getSize() < 20)
			if (timePerFireWork >= 1.0f / frequency) {
				timePerFireWork = 0.0f;
				addNewFireWork(camera.getPosition().x, camera.getPosition().y,
				WINDOWSIZE_W,WINDOWSIZE_H);
			}
	int x = 0;
	//display message
	textureCollection->at(42)->render(x, x, (int)camera.getSize().w, (int)camera.getSize().h,0);
	//display fire work in red color
	for (Node<FireWork*>*iter = fireWork.getFirstNode(); iter != fireWork.tail; iter = iter->next)
	{
		iter->data->display(camera);
		if (iter->data->isDead()) 
			iter = fireWork.delNode(iter);
		
	}
}

bool YouWin::done() const
{
	return (timeDisplay<=0&&fireWork.isEmpty());
}

void YouWin::addNewFireWork(float x, float y,float w, float h)
{
	FireWork*newFireWork = new FireWork(
		x+(float)(rand() % (int)(w*0.5f))+w*0.25f, y+h,
		textureCollection->at(2), textureCollection->at(3), soundCollection->at(0));
	fireWork.addFirst(newFireWork);
}

FireWork::FireWork(float x, float y,
	 Texture * texture, Texture * texture2,Sound*sound)
	:texture(texture),texture2(texture2),sound(sound)
{
	position.set(x, y);
	velocity.set(0, -(float)(rand() % 7 + 28));
	damping = (float)(rand()%10+90)/100.0f;
	dead = false;
	size = 50.0f;
	flip = (rand()%100>50);
}

FireWork::~FireWork()
{
	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next)
	{
		delete iter->data;
		iter->data = NULL;
	}
	texture = NULL;
	texture2 = NULL;
	sound = NULL;
	position.set(0.0f, 0.0f);
	dead = false;
	size = 0.0f;
}

void FireWork::display(const Camera&camera)
{
	//update
	float gravity = 0.1f;
	acceleration.y += gravity;
	velocity.add(&acceleration);
	velocity.multiply(damping);
	position.add(&velocity);
	acceleration.y = 0.0f;
	if (explosion.isEmpty()) {
		if (velocity.y >= -1.5f) {
			Explosion*newExplosion = new Explosion();
			newExplosion->setup(new Vector2D(&position), texture2, sound);
			explosion.addFirst(newExplosion);
		}
		texture->render(camera, position.x - camera.getPosition().x - size*0.5f,
			position.y - camera.getPosition().y - size*0.5f, size, size, 0,velocity.y*0.05f,flip);
	}

	for (Node<Explosion*>*iter = explosion.getFirstNode(); iter != explosion.tail; iter = iter->next)
	{
		iter->data->display(camera);
		if (iter->data->isDead()) {
			delete iter->data;
			iter->data = NULL;
			iter = explosion.delNode(iter);
			dead = true;
		}
	}
}

bool FireWork::isDead() const
{
	return dead;
}
