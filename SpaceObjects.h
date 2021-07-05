
									//Abstract Class 

#ifndef SPACEOBJECTS_H_
#define SPACEOBJECTS_H_

#include <iostream>
#include <string>

#include "util.h"
#include "Point.h"

using namespace std;


class SpaceObjects
{

private:

	string Name;	//ID for Collision Detection
	int healthCount;	// Number of Lives
	Point Position;		// X_Cordinate and Y_Cordinate of the Baord -->Conversion to int on Board
	float Radius;		//Radius for Drawing Objects and Collision Detection
	float velocity_X;	// Increase Speed in X_axis
	float velocity_Y;	// Increase Speed in X_axis
	float Angle;		//Angle for Movement of the Ships and Bullets 

public:

	SpaceObjects(string ,float ,float ,float ,float ,float,float,int);
	
	//Getters

	int getHealthCount()const;
	float getX()const;
	float getY()const;
	float getAngle()const;
	float getVelocityX()const;
	float getVelocityY()const;
	float getRadius()const;

	//Setters
	void setHealthCount(int);
	void setX(float);
	void setY(float);
	void setRadius(float);
	void setAngle(float);
	void setVelocity(float, float);
	void setVelocityX(float);
	void setVelocityY(float);
	void setName(string);
	string getName()const;

	//Pure Virtual Functions 
	virtual void Move()=0;
	virtual void Draw() = 0;
	
	virtual ~SpaceObjects();
};
#endif