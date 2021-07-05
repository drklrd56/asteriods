#ifndef SIMPLEENEMY_H_
#define SIMPLEENEMY_H_

#include "EnemyShip.h"
class SimpleEnemy:public EnemyShip
{
	float Ship_ver[3][2];
public:
	SimpleEnemy(string, float, float, float, float dx, float dy, float);
	void Draw();
	void Move();
	virtual ~SimpleEnemy();
};

#endif