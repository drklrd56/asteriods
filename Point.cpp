#include "Point.h"



Point::Point()
{
}

Point::Point(float x, float y)
{
	setX(x);
	setY(y);
}

float Point::getX() const
{
	return Position_X;
}

float Point::getY() const
{
	return Position_Y;
}

void Point::setX(float x)
{
	Position_X = x;
}

void Point::setY(float y)
{
	Position_Y = y;
}

Point::~Point()
{
}
