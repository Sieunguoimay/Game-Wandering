#include "Camera.h"



Camera::Camera(Size*windowSize)
:size(windowSize)
{
	//size = new Size(windowSize->w,windowSize->h);
	location.set(-size->w/3,0);
	velocity.set(0.0f,0.0f);
	acceleration.set(0.0f,0.0f);
	desired.set(0.0f,0.0f);
	target.set(0.0f,0.0f);
	maxForce = 5.0f;
	maxSpeed = 12.0f;
}


Camera::~Camera()
{
	location.set(0.0f,0.0f);
	velocity.set(0.0f,0.0f);
	acceleration.set(0.0f,0.0f);
	desired.set(0.0f,0.0f);
	target.set(0.0f,0.0f);
	size = NULL;
	maxForce = 0.0f;
	maxSpeed = 0.0f;
}


void Camera::reset()
{
	location.set(-size->w / 3.0f, 0.0f);
	velocity.set(0.0f,0.0f);
	acceleration.set(0.0f,0.0f);
	desired.set(0.0f,0.0f);
	target.set(0.0f,0.0f);
}

void Camera::setTarget(float x, float y)
{
	target.set(x, y);
}

void Camera::update()
{
	float x = target.x - (size->w/2.0f)*WINDOWSIZE_W/size->w;
	float y = target.y - (size->h *2.0f/3.0f)*WINDOWSIZE_H/size->h;

	if (target.y*size->w / WINDOWSIZE_W > location.y+size->h||
		location.y+target.y*size->w / WINDOWSIZE_W < size->h/3.0f)
		desired.set(x, y);
	else
		desired.set(x, 0.0f);//set like that in order to camera just go right or left

	//calculate desired velocity
	desired.subtract(location);
	float d = desired.magnitude();
	desired.normalize();

	if (d < 50.0f) {
		float m = UtilityFunctions::map(d, 0.0f, 50.0f, 0.0f, maxSpeed);//the closer the smaller maxspeed is
		desired.multiply(m);
	}
	else desired.multiply(maxSpeed);

	//calculate steering force
	desired.subtract(velocity);//this vector now is steering for
	desired.limit(maxForce);

	acceleration.set(desired);

	velocity.add(acceleration);
	location.add(velocity);

}

const Vector2D&Camera::getPosition()const
{
	return location;
}

const Size & Camera::getSize() const
{
	// TODO: insert return statement here
	return *size;
}
