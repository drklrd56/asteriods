#ifndef ENEMYSHIP_H_
#define	ENEMYSHIP_H_

#include "SpaceShip.h"

class EnemyShip:public SpaceShip
{
public:
	EnemyShip(string, float, float, float, float dx, float dy, float);
	virtual ~EnemyShip();
};

#endif