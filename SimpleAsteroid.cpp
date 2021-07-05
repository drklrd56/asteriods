#include "SimpleAsteroid.h"

SimpleAsteroid::SimpleAsteroid(string name,float x, float y, float r, float c, float dx, float dy,float angle)
	:Asteroid(name,x, y, r, c , dx , dy,angle,1)
{
}

void SimpleAsteroid::Move()
{
	//Move in Specific Direction With the Pre_Defined Velocity

	this->setX(this->getX() + this->getVelocityX());
	this->setY(this->getY() + this->getVelocityY());
}

void SimpleAsteroid::Draw()
{

	//Modified Version of the Game.cpp Draw Asteroids Fuction 

	glPushMatrix();

	float x = this->getX();
	float y = this->getY();

	const int nvertices = 722;
	GLfloat vertices[nvertices][2];
	glColor3fv(colors[WHITE]);
	float degree = M_PI / (getCorners() / 2);
	float Angle = 0;
	float Start=0, Start_Angle=0;
	float *points = this->getPoint();
	for (int i = 0; i <= getCorners(); ++i)
	{
		if (i == getCorners())
		{
			vertices[i][0] = Start * cos(Start_Angle);
			vertices[i][1] = sin(Start_Angle)*Start;
		}
		else
		{
			vertices[i][0] = cos(Angle)*points[i];
			vertices[i][1] = sin(Angle)*points[i];
		}
		if (i == 0)Start = points[i], Start_Angle = Angle;
		Angle += degree;
	}
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= getCorners(); ++i)
	{
		glVertex4f(x + vertices[i][0], y + vertices[i][1], 0,1);
	}
	glEnd();
	glPopMatrix();
}

SimpleAsteroid::~SimpleAsteroid()
{
}
