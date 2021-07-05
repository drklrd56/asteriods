#ifndef BULLET_H_
#define BULLET_H_

#include "SpaceObjects.h"
class Bullets :public SpaceObjects
{
public:
	Bullets();
	Bullets(float, float, float, float);

	// Function Delatration of Base Class's Pure Virtual Ones.
	void Draw();
	void Move();

	//Overloaded = for Bullets Addition Specification in the Ship Class
	Bullets& operator=(Bullets &);

	virtual ~Bullets();
};

#endif