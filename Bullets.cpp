#include "Bullets.h"



Bullets::Bullets():SpaceObjects("Bullets",0,0,0,0,0,0,0)
{
}

Bullets::Bullets(float x, float y, float radius, float angle)
	:SpaceObjects("Bullets",x,y,radius,4,4,angle,1)
{
}

void Bullets::Draw()
{
	//Red Color 

	float *color;
	float x = 1;
	color = &x;
	DrawCircle(this->getX(), this->getY(), this->getRadius(),color);
}

void Bullets::Move()
{
	this->setX(this->getX() + (this->getVelocityX() + sin(getAngle()) * 2));
	this->setY(this->getY() + (this->getVelocityY() - cos(getAngle()) * 2));
}
Bullets & Bullets::operator=(Bullets &obj)
{
	this->setX(obj.getX());
	this->setY(obj.getY());
	this->setVelocityX(obj.getVelocityX());
	this->setVelocityY(obj.getVelocityY());
	this->setRadius(obj.getRadius());
	this->setHealthCount(1);
	this->setName("Bullets");
	this->setAngle(obj.getAngle());
	return *this;
}
Bullets::~Bullets()
{

}
