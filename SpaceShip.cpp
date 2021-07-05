#include "SpaceShip.h"

SpaceShip::SpaceShip(string name,float x, float y, float radius, float dx, float dy, float angle,int healthCount)
	:SpaceObjects(name,x, y, radius, dx, dy,angle,healthCount)
{
	bullets = NULL;
	bulletCount = 0;
}

void SpaceShip::setCoOrdinates(float arr[][2])
{
	for (int i = 0; i < 3; i++)
	{
		Ship_Cor[i][0] = arr[i][0];
		Ship_Cor[i][0] = arr[i][0];
	}
}

void SpaceShip::DrawBullets()
{
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i].Draw();
	}
}

void SpaceShip::Shoot()
{

	Bullets *temp=new Bullets[bulletCount + 1];

	for (int i = 0; i < bulletCount; i++)
	{
		temp[i] = bullets[i];
	}

	temp[bulletCount].setX(this->getX());
	temp[bulletCount].setY(this->getY());
	temp[bulletCount].setRadius(2);
	temp[bulletCount].setAngle(this->getAngle());
	//Default Health Count 1 .
	
	bullets = NULL;
	if (bulletCount > 0)
	{
		delete[]bullets;
	}
	else
	{
		delete bullets;
	}

	bulletCount += 1;
	this->bullets = new Bullets[bulletCount];
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i] = temp[i];
	}
	temp = NULL;
	if (bulletCount > 0)
	{
		delete[]temp;
	}
	else
	{
		delete temp;
	}

}
void SpaceShip::RemoveBullet(int index)
{
	if(bulletCount>0)
		bulletCount -= 1;
}
void SpaceShip::MoveBullets()
{
	for (int i = 0; i < bulletCount; i++)
	{
		bullets[i].Move();
	}
}
int SpaceShip::getCount()
{
	return bulletCount;
}
Bullets * SpaceShip::getBulllets()
{
	return bullets;
}
float ** SpaceShip::getCoOrdinates() const
{
	float **arr = new float *[3];
	for (int i = 0; i < 3; i++)
	{
		arr[i] = new float[2];
		for (int j = 0; j < 2; j++)
		{
			arr[i][j] = Ship_Cor[i][j];
		}
	}
	return arr;
}
void SpaceShip::Shipfloat()
{
	this->setX(this->getX() +(sin(getAngle())/10));
	this->setY(this->getY() - (cos(getAngle()) / 10));
}
SpaceShip::~SpaceShip()
{

}