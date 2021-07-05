#include "EnemyShip.h"



EnemyShip::EnemyShip(string name,float x, float y, float radius, float dx, float dy, float angle)
	:SpaceShip(name,x, y, radius+10, dx, dy, angle,1)
{
}
EnemyShip::~EnemyShip()
{
}
