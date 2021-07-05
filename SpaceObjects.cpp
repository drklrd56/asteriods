#include "SpaceObjects.h"



SpaceObjects::SpaceObjects(string name,float x,float y,float radius, float dx, float dy,float angle,int lifeCount)
{
	Name = name;
	healthCount = lifeCount;
	Position.setX(x);
	Position.setY(y);
	Radius = radius;
	velocity_X = dx;
	velocity_Y = dy;
	Angle = angle;
}

void SpaceObjects::setHealthCount(int lifeCount)
{
	healthCount = lifeCount;
}

int SpaceObjects::getHealthCount() const
{
	return healthCount;
}

void SpaceObjects::setX(float x)
{
	Position.setX(x);
}

void SpaceObjects::setY(float y)
{
	Position.setY(y);
}

float SpaceObjects::getX() const
{
	return Position.getX();
}

float SpaceObjects::getY() const
{
	return Position.getY();
}

void SpaceObjects::setVelocity(float dx, float dy)
{
	velocity_X = dx;
	velocity_Y = dy;
}

float SpaceObjects::getVelocityX() const
{
	return velocity_X;
}

float SpaceObjects::getVelocityY() const

{
	return velocity_Y;
}

void SpaceObjects::setVelocityX(float dx)

{
	velocity_X = dx;
}

void SpaceObjects::setVelocityY(float dy)

{
	velocity_Y = dy;
}

void SpaceObjects::setRadius(float r)
{
	if (r > 0)
		Radius = r;
}

float SpaceObjects::getRadius() const
{
	return Radius;
}
void SpaceObjects::setAngle(float angle)
{
	Angle = angle;
}
float SpaceObjects::getAngle()const
{
	return Angle;
}

void SpaceObjects::setName(string name)
{
	Name = name;
}

string SpaceObjects::getName() const
{
	return Name;
}

SpaceObjects::~SpaceObjects()
{
}
