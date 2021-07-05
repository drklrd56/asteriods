#include "SimpleEnemy.h"



SimpleEnemy::SimpleEnemy(string name, float x, float y, float radius, float dx, float dy, float angle)
	:EnemyShip(name, x, y, radius, dx, dy, angle)
{
	float points[3][2] = { { 0.0, -radius },{ -radius,radius },{ radius,radius } };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Ship_ver[i][j] = points[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		points[i][0] = x + Ship_ver[i][0];
		points[i][0] = y + Ship_ver[i][1];
	}
	setCoOrdinates(points);
}

void SimpleEnemy::Draw()
{
	float *color = new float[3];
	float x = 1;
	for (int i = 0; i < 3; i++)
	{
		color[i] = x;
	}
	//Rotation Check
	float arr[3][2];
	for (int i = 0; i < 3; i++)
	{
		arr[i][0] = Ship_ver[i][0] * cos(getAngle()) - Ship_ver[i][1] * sin(getAngle());
		arr[i][1] = Ship_ver[i][0] * sin(getAngle()) + Ship_ver[i][1] * cos(getAngle());
	}
	for (int i = 0; i < 3; i++)
	{
		arr[i][0] += this->getX();
		arr[i][1] += this->getY();
	}
	setCoOrdinates(arr);
	DrawTriangle(arr[0][0], arr[0][1], arr[1][0], arr[1][1], arr[2][0],
		arr[2][1], color);
}

void SimpleEnemy::Move()
{
	this->setX(this->getX() + this->getVelocityX());
	this->setY(this->getY() + this->getVelocityY());
}


SimpleEnemy::~SimpleEnemy()
{
}
