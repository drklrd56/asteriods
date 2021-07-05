#include "ComplexAsteroid.h"



ComplexAsteroid::ComplexAsteroid(string name,float x, float y, float r, float c, float dx, float dy,float angle)
	:Asteroid(name,x, y, r, c, dx, dy,angle,3)
{
}

void ComplexAsteroid::Draw()
{
	glPushMatrix();
	float x = this->getX();
	float y = this->getY();
	const int nvertices = 722;
	GLfloat vertices[nvertices][2];
	glColor3fv(colors[WHITE]);
	glBegin(GL_LINE_LOOP);
	float degree = M_PI / (getCorners() / 2);
	float Angle = 0;
	float Start = 0, Start_Angle = 0;
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
	for (int i = 0; i <= getCorners(); ++i)
	{
		glVertex4f(x + vertices[i][0], y + vertices[i][1], 0, 1);
	}
	glEnd();
	glPopMatrix();
}

void ComplexAsteroid::Move()
{

	this->setX(this->getX() + this->getVelocityX());
	this->setY(this->getY() + this->getVelocityY());
}

//The Fuction Which Changes the Direction of the Asteroid At random.The Only Difference between the 
// Simple and Complex Asteroids.

void ComplexAsteroid::ChangePosition()
{
	int choice = GetRandInRange(1,5);
		switch (choice)
		{
		case 1:
			this->setVelocity(-getVelocityX(), -getVelocityY());
			break;
		case 2:
			this->setVelocity(-getVelocityX(), getVelocityY());
			break;
		case 3:
			this->setVelocity(getVelocityX(), -getVelocityY());
			break;
		case 4:
			if (getVelocityX() < 0)
			{
				setVelocityX(getVelocityX()*-1);
			}
			if (getVelocityY() < 0)
			{
				setVelocityY(getVelocityY()*-1);
			}
			this->setVelocity(getVelocityX(), getVelocityY());
			break;
		}
}

ComplexAsteroid::~ComplexAsteroid()
{
}
