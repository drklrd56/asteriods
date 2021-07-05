
// Class For Simple Asteroids and its Functionalities.Inherited for Asteroids

#ifndef SIMPLEASTEROID_H_
#define SIMPLEASTEROID_H_

#include "Asteroid.h"

class SimpleAsteroid:public Asteroid
{
	//No private Data Members Required

public:

	SimpleAsteroid(string, float, float, float, float, float, float, float);

	// Function Delatration of Base Class's Pure Virtual Ones.

	void Draw();
	void Move();

	virtual ~SimpleAsteroid();
};

#endif
