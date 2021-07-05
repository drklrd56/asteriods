#ifndef GAMEINTERFACE_H_
#define GAMEINTERFACE_H_

#include "SimpleAsteroid.h"
#include "ComplexAsteroid.h"
#include "ComplexEnemy.h"
#include "MySpaceShip.h"
#include "SimpleEnemy.h"
#include "Bullets.h"
#include "Board.h"

class GameInterface
{
private:
	Board * b;
	SpaceShip *Ships[2];
	Asteroid **Asteroids;

	float STARTING_RADIUS;
	float MEDIUM_RADIUS;
	float SMALL_RADIUS;
	float MYSHIPRADIUS;
	float ENEMYSHIPRADIUS;

	bool IntoHyperSpace;
	int Score ;
	int level ;
	bool Float ;
	bool isDrawn ;
	bool isEnemy ;
	int HyperCount;
	int callEnemy;
	int shootInterval;
	int Eshoot;
	int call;
	int ScoreCheck ;
	int asteroidCount;
	int shipCount;
	bool gameOver;
	int Board_Width, Board_Height;
	int ComplexChangeDir;
	int ShipCoolDown;
	string DrawScore ;
	string DrawLives ;
	int text_X, text_Y;
	int Lives_X ;
	bool CheckNow;
	void CreateObjects();
	void DrawObjects();
	void MoveObjects();
	void MoveBullets();
	void WrapBoard(SpaceObjects &);
	void ObjectsCollision();
	void UpdateAsteroids(int index);
	void ShipCollision();
	void AddEnemyShips();
	void ChangeComplexDirections();
	void MovetoNextLevel();
	float distance(float, float, float, float);
	void WrapObjects();
public:
	GameInterface(Board &, int height, int width);
	void StartGame();
	void MoveShip();
	float getShipAngle();
	void setShipAngle(float value);
	void setFloat(bool);
	void EnterHyperSpace(bool);
	void Shoot();
	~GameInterface();
};
#endif