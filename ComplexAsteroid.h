
// Class For Simple Asteroids and its Functionalities.Inherited for Asteroids

#ifndef COMPLEXASTEROID_H_
#define COMPLEXASTEROID_H_

#include "Asteroid.h"

class ComplexAsteroid:public Asteroid
{
	//No Private Data Members Required.
public:
	ComplexAsteroid(string, float, float, float, float, float, float, float);

	// Function Delatration of Base Class's Pure Virtual Ones.
	void Draw();
	void Move();

	//Function to Move the Asteroid in a Random Direction.
	void ChangePosition();

	virtual ~ComplexAsteroid();
};


#endif 