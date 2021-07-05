
								//Abstract Class

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "SpaceObjects.h"

class Asteroid:public SpaceObjects
{
private:

	float *points;	// To save andomly generated points an to draw asteroids using them.
	int Corners;	// Number of Corners of an Asteriod

public:

	Asteroid(string ,float , float , float , float , float , float ,float ,int );

	//Getters
	float* getPoint()const;
	int getCorners()const;

	//Setters
	void setCorners(int);
	void setPoints(float *,int);
	virtual ~Asteroid();
};

#endif