
								// Player Ship
#ifndef MYSPACESHIP_H_
#define MYSPACESHIP_H_

#include "SpaceShip.h"

class MySpaceShip :public SpaceShip
{
private:
	float Ship_ver[3][2];//Basic Ship Structure each time the ship moves its draw according to this
	//structure construct of the cordinates its moves to.
public:
	MySpaceShip(string,float, float, float, float dx, float dy, float);

	// Function Delatration of Base Class's Pure Virtual Ones.
	void Draw();
	void Move();

	~MySpaceShip();
};

#endif