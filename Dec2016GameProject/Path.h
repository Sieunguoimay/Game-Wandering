#ifndef PATH_H
#define PATH_H
#include"globalheader.h"
class Path{
public:
	Path(float x,float y);
	~Path();
	LinkedList<Vector2D*>paths;
	Vector2D position;
	float radius;
};
#endif //PATH_H
