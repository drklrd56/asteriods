#ifndef COMPLEXENEMY_H_
#define COMPLEXENEMY_H_

#include "EnemyShip.h"
class ComplexEnemy:public EnemyShip
{
	int Ship_ver[3][2];
public:
	ComplexEnemy(string, float, float, float, float dx, float dy, float);
	void Draw();
	void Move();
	void ChangeDirection();
	virtual ~ComplexEnemy();
};

#endif