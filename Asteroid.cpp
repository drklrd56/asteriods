#include "Asteroid.h"


Asteroid::Asteroid(string name, float x, float y, float r, float c, float dx, float dy, float angle, int hc)
	:SpaceObjects(name,x, y, r, dx, dy, angle,hc)
{
	Corners = c;
	points = new float[Corners];
	for (int index = 0; index < Corners; index++)
	{
		points[index] = GetRandInRange(getRadius()/2, getRadius()+1);
	}

}

void Asteroid::setCorners(int corners)
{
	if (corners > 0)
		Corners = corners;
}
int Asteroid::getCorners() const
{
	return Corners;
}
float * Asteroid::getPoint() const
{
	return points;
}
void Asteroid::setPoints(float *arr,int corners)
{
	setCorners(corners);
	for (int i = 0; i < corners; i++)
	{
		points[i] = arr[i];
	}
}
Asteroid::~Asteroid()
{
}
