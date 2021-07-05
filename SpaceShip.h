
							//Abstract Class

#ifndef SPACESHIP_H_
#define SPACESHIP_H_


#include <iostream>
#include "SpaceObjects.h"
#include "Bullets.h"

using namespace std;

class SpaceShip:public SpaceObjects
{
private:
	Bullets *bullets;	//Composition of Bullets as it is a Property of the SpaceShip.
	float Ship_Cor[3][2];	//Store the Basic Ship Struction that is an Triangle with vertices..
	//	This Variable stores the new  Position of the cordinates as the Ship moves.
	int bulletCount;	// Count of the Bullets Fired.

public:
	SpaceShip(string,float ,float,float,float dx, float dy, float,int);

	//Getters
	int getCount();
	float** getCoOrdinates()const;	// Get Cordinates of the Ship

	//Setters
	void setCoOrdinates(float[][2]);
	
	//Bullet Related Functions 
	Bullets* getBulllets();	//	Get Bullets Fired By the Ship.
	void DrawBullets();	//As its Composition so I have to Provide this function for Main access to Bullets
	void Shoot();	// Ships Property to Shoot
	void RemoveBullet(int index);	//Removal Of Bullets
	void MoveBullets();	//Movement of Bullets
	
	void Shipfloat();	//Movement of Ship if No key is Pressed.Extra Functionatily just to add folating affect.
	
	virtual ~SpaceShip();
};

#endif