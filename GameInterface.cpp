#include "GameInterface.h"

GameInterface::GameInterface(Board & board, int width, int height)
{
	b = &board;
	Board_Width = width;
	Board_Height = height;
	IntoHyperSpace = false;
	HyperCount = 0;
	STARTING_RADIUS = 1.2 * b->GetCellSize();
	MEDIUM_RADIUS = STARTING_RADIUS / 1.5;
	SMALL_RADIUS = STARTING_RADIUS / 2.0;

	ENEMYSHIPRADIUS = b->GetCellSize() / 3;
	MYSHIPRADIUS = b->GetCellSize() / 2;

	callEnemy = GetRandInRange(4000,9000);
	shootInterval = GetRandInRange(500, 1000);
	Eshoot=0;
	call = 0;
	shipCount = 2;
	gameOver = false;
	ComplexChangeDir = 0;
	ShipCoolDown = 0;
	DrawScore = "";
	DrawLives = "";
	text_X = 60, text_Y = 580;
	Lives_X = 700;
	CheckNow = true;
	Score = 0;
	level = 1;
	Float = false;
	isDrawn = false;
	isEnemy = false;
	ScoreCheck = 0;
}

void GameInterface::CreateObjects()
{
	asteroidCount = GetRandInRange(1, 7);
	float xVelocity = 0.35;
	float yVelocity = 0.35;
	int xi = 0, yi = 0;
	if (level == 1)
	{
		Ships[0] = new MySpaceShip("Saucer", Board_Width / 2, Board_Height / 2, b->GetCellSize() / 2, 1, 1, 150);
		Ships[1] = NULL;
	}
	Asteroids = new Asteroid *[asteroidCount];
	for (int i = 0; i < asteroidCount; i++)
	{
		Asteroids[i] = NULL;
	}
	for (int i = 0; i <asteroidCount; i++)
	{
		if (i % 2 == 0)
		{
			xVelocity *= -1;
			yVelocity *= -1;
		}
		b->GetInitRandomPosition(xi, yi);
		while (xi == (Ships[0]->getX() / 2-50) || xi == (Ships[0]->getX() + 50) || xi == (Ships[0]->getX()))
		{
			b->GetInitRandomPosition(xi, yi);
		}
		Asteroids[i] = new SimpleAsteroid("Simple", xi, yi, STARTING_RADIUS, 10, xVelocity, yVelocity, 0);
	}
}

void GameInterface::DrawObjects()
{
	for (int i = 0; i < asteroidCount; i++)
	{
		Asteroids[i]->Draw();
	}
	for (int i = 0; i < shipCount; i++)
	{
		if (Ships[i] != NULL)
		{
			Ships[i]->Draw();
		}
	}
}

void GameInterface::MoveObjects()
{
	for (int i = 0; i < asteroidCount; i++)
	{
		Asteroids[i]->Move();
	}
	if (Ships[1] != NULL)
	{
		Ships[1]->Move();
	}
}

void GameInterface::MoveShip()
{
	Ships[0]->Move();
}

void GameInterface::MoveBullets()
{
	Bullets *bullets;
	int count = 0;
	for (int i = 0; i < shipCount; i++)
	{
		if (Ships[i] != NULL)
		{
			Ships[i]->DrawBullets();
			Ships[i]->MoveBullets();
			bullets = Ships[i]->getBulllets();
			count = Ships[i]->getCount();
			for (int j = 0; j < count; j++)
			{
				if (bullets[j].getX() < 0 || bullets[j].getX() > Board_Width || bullets[j].getX() < 0
					|| bullets[j].getY() > Board_Height)
				{
					Ships[i]->RemoveBullet(j);
				}
			}
		}
	}
	bullets = NULL;
	if (count > 0)
	{
		delete[]bullets;
	}
	else
	{
		delete bullets;
	}
}

void GameInterface::WrapBoard(SpaceObjects &pos)
{
	if (pos.getX() < 0)pos.setX(pos.getX() + Board_Width);
	if (pos.getX() > Board_Width) pos.setX(pos.getX() - Board_Width);
	if (pos.getY() < 0)pos.setY(pos.getY() + Board_Height);
	if (pos.getY() > Board_Height)pos.setY(pos.getY() - Board_Height);
}

float GameInterface::getShipAngle()
{
	return Ships[0]->getAngle();
}

void GameInterface::setShipAngle(float value)
{
	Ships[0]->setAngle(value);
}

void GameInterface::setFloat(bool tof)
{
	Float = tof;
}

void GameInterface::Shoot()
{
	Ships[0]->Shoot();
}

GameInterface::~GameInterface()
{
	for (int i = 0; i < asteroidCount; i++)
	{
		Asteroids[i] = NULL;
	}
	delete[]Asteroids;
	for (int i = 0; i < shipCount; i++)
	{
		Ships[i] = NULL;
	}
	delete[]Ships;
	delete[]b;
}

void GameInterface::ObjectsCollision()
{
	//BULLETS SHOT BY THE PLAYER SHIP CHECK
	Bullets *bullets;
	int count = 0;
	bullets = Ships[0]->getBulllets();
	count = Ships[0]->getCount();
	float Distance;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < asteroidCount; j++)
		{
			Distance = distance(bullets[i].getX(), bullets[i].getY(), Asteroids[j]->getX(),
				Asteroids[j]->getY());
			if (Distance <= (bullets[i].getRadius() + Asteroids[j]->getRadius()))
			{
				UpdateAsteroids(j);
				Ships[0]->RemoveBullet(i);
			}
		}
		if (isEnemy == true)
		{
			if (bullets[i].getX()<=Ships[1]->getX() && bullets[i].getY()<=Ships[1]->getY())
			{
				Distance = distance(bullets[i].getX(), bullets[i].getY(), Ships[1]->getX(), Ships[1]->getY());
					if (Distance <= (bullets[i].getRadius()+Ships[0]->getRadius()))
					{
						shipCount = 1;
						Ships[0]->RemoveBullet(i);
						if (Ships[1]->getName() == "ComplexEnemy")
						{
							Score += 500;
							ScoreCheck += 500;
						}
						if (Ships[1]->getName() == "SimpleEnemy")
						{
							Score += 100;
							ScoreCheck += 100;
						}
						Ships[1] = NULL;
						isEnemy = false;
					}
			}
		}
	}
	bullets = NULL;
	if (count > 0)
	{
		delete[]bullets;
	}
	else
	{
		delete bullets;
	}
}

void GameInterface::UpdateAsteroids(int index)
{
	int Increase_Objects = 0;
	int type = 0;
	bool Update = false;
	int count;

	Asteroid **temp;
	int index_save = 0;

	float x = Asteroids[index]->getX();
	float y = Asteroids[index]->getY();
	float dx = Asteroids[index]->getVelocityX();
	float dy = Asteroids[index]->getVelocityY();
	int corners = GetRandInRange(6, 11);

	if (Asteroids[index]->getRadius() == STARTING_RADIUS)
	{
		Asteroids[index] = NULL;
		Asteroids[index] = new ComplexAsteroid("Complex", x - 5, y - 5, MEDIUM_RADIUS, corners
			, dx + 0.1, -dy, 0);

		Increase_Objects = 1;
		Update = true;
		Score += 10;
		ScoreCheck += 10;
		type = 1;
	}
	else if (Asteroids[index]->getRadius() == MEDIUM_RADIUS)
	{
		Asteroids[index]->setHealthCount(Asteroids[index]->getHealthCount() - 1);
		if (Asteroids[index]->getHealthCount() <= 0)
		{
			Asteroids[index] = NULL;
			Asteroids[index] = new SimpleAsteroid("Simple", x - 5, y - 10,
				SMALL_RADIUS, corners, dx + 0.1, -dy + 0.1, 0);
			Increase_Objects = 3;
			Update = true;
			Score += 20;
			ScoreCheck += 20;
			type = 2;
		}
	}
	else if (Asteroids[index]->getRadius() == SMALL_RADIUS)
	{
		Score += 40;
		ScoreCheck += 40;
		count = asteroidCount - 1;
		temp = new Asteroid*[count];
		int index_main = 0;
		for (int index_save = 0; index_save < asteroidCount; index_save++)
		{
			if (index_save != index)
			{
				if (Asteroids[index_save]->getName() == "Complex")
				{
					temp[index_main] = new ComplexAsteroid(Asteroids[index_save]->getName(), Asteroids[index_save]->getX(),
						Asteroids[index_save]->getY(), Asteroids[index_save]->getRadius(), Asteroids[index_save]->getCorners(),
						Asteroids[index_save]->getVelocityX(), Asteroids[index_save]->getVelocityY(), Asteroids[index_save]->getAngle());
					temp[index_main]->setPoints(Asteroids[index_save]->getPoint(), Asteroids[index_save]->getCorners());
				}
				if (Asteroids[index_save]->getName() == "Simple")
				{
					temp[index_main] = new SimpleAsteroid(Asteroids[index_save]->getName(), Asteroids[index_save]->getX(),
						Asteroids[index_save]->getY(), Asteroids[index_save]->getRadius(), Asteroids[index_save]->getCorners(),
						Asteroids[index_save]->getVelocityX(), Asteroids[index_save]->getVelocityY(), Asteroids[index_save]->getAngle());
					temp[index_main]->setPoints(Asteroids[index_save]->getPoint(), Asteroids[index_save]->getCorners());
				}
				index_main++;
			}
		}
		for (int i = 0; i < asteroidCount; i++)
		{
			Asteroids[i] = NULL;
		}
		delete[]Asteroids;
		asteroidCount -= 1;
		Asteroids = new Asteroid*[asteroidCount];
		for (int i = 0; i < asteroidCount; i++)
		{
			if (temp[i]->getName() == "Complex")
			{
				Asteroids[i] = new ComplexAsteroid(temp[i]->getName(), temp[i]->getX(), temp[i]->getY(),
					temp[i]->getRadius(), temp[i]->getCorners(), temp[i]->getVelocityX(),
					temp[i]->getVelocityY(), temp[i]->getAngle());
				Asteroids[i]->setPoints(temp[i]->getPoint(), temp[i]->getCorners());
			}
			if (temp[i]->getName() == "Simple")
			{
				Asteroids[i] = new SimpleAsteroid(temp[i]->getName(), temp[i]->getX(), temp[i]->getY(),
					temp[i]->getRadius(), temp[i]->getCorners(), temp[i]->getVelocityX(),
					temp[i]->getVelocityY(), temp[i]->getAngle());
				Asteroids[i]->setPoints(temp[i]->getPoint(), temp[i]->getCorners());
			}
		}
		Update = false;
		for (int i = 0; i < count; i++)
		{
			temp[i] = NULL;
		}
		delete[]temp;
	}
	if (Update == true)
	{
		count = asteroidCount + Increase_Objects;
		temp = new Asteroid*[count];
		for (int i = 0; i < count; i++)
		{
			if (i < asteroidCount)
			{
				if (Asteroids[i]->getName() == "Complex")
				{
					temp[i] = new ComplexAsteroid(Asteroids[index_save]->getName(), Asteroids[index_save]->getX(),
						Asteroids[index_save]->getY(), Asteroids[index_save]->getRadius(), Asteroids[index_save]->getCorners(),
						Asteroids[index_save]->getVelocityX(), Asteroids[index_save]->getVelocityY(), Asteroids[index_save]->getAngle());
					temp[i]->setPoints(Asteroids[index_save]->getPoint(),Asteroids[index_save]->getCorners());
				}
				if (Asteroids[i]->getName() == "Simple")
				{
					temp[i] = new SimpleAsteroid(Asteroids[index_save]->getName(), Asteroids[index_save]->getX(),
						Asteroids[index_save]->getY(), Asteroids[index_save]->getRadius(), Asteroids[index_save]->getCorners(),
						Asteroids[index_save]->getVelocityX(), Asteroids[index_save]->getVelocityY(), Asteroids[index_save]->getAngle());
					temp[i]->setPoints(Asteroids[index_save]->getPoint(), Asteroids[index_save]->getCorners());
				}
				index_save++;
			}
			else
			{
				if (i % 2 == 0)
				{
					dy += 0.1;
					dx += 0.1;
				}
				else
				{
					dy = -dy;
					dy -= 0.1;
					dx = -dx - 0.1;
				}
				if (type == 1)
				{

					temp[i] = new ComplexAsteroid("Complex", x + (5 *i), (y - 5), MEDIUM_RADIUS, corners
						, dx + 0.1, dy, 0);
				}
				if (type == 2)
				{
					temp[i] = new SimpleAsteroid("Simple", x + (50 + i), y - (50 + i), SMALL_RADIUS, corners, dx
						+ 0.1, dy + 0.1, 0);

				}
			}
		}
		for (int i = 0; i < asteroidCount; i++)
		{
			Asteroids[i] = NULL;
		}
		delete[]Asteroids;
		asteroidCount += Increase_Objects;
		Asteroids = new Asteroid*[asteroidCount];
		for (int i = 0; i < asteroidCount; i++)
		{
			if (temp[i]->getName() == "Complex")
			{
				Asteroids[i] = new ComplexAsteroid(temp[i]->getName(), temp[i]->getX(), temp[i]->getY(),
					temp[i]->getRadius(), temp[i]->getCorners(), temp[i]->getVelocityX(),
					temp[i]->getVelocityY(), temp[i]->getAngle());
				Asteroids[i]->setPoints(temp[i]->getPoint(), temp[i]->getCorners());
			}
			if (temp[i]->getName() == "Simple")
			{
				Asteroids[i] = new SimpleAsteroid(temp[i]->getName(), temp[i]->getX(), temp[i]->getY(),
					temp[i]->getRadius(), temp[i]->getCorners(), temp[i]->getVelocityX(),
					temp[i]->getVelocityY(), temp[i]->getAngle());
				Asteroids[i]->setPoints(temp[i]->getPoint(), temp[i]->getCorners());
			}
		}
		for (int i = 0; i < count; i++)
		{
			temp[i] = NULL;
		}
		delete[]temp;
	}

}

void GameInterface::ShipCollision()
{
	float Distance;
	if (CheckNow == true)
	{
		for (int i = 0; i < asteroidCount; i++)
		{
			Distance = distance(Ships[0]->getX(), Ships[0]->getY(), Asteroids[i]->getX(),
				Asteroids[i]->getY());
			if (Distance <= (Ships[0]->getRadius() + Asteroids[i]->getRadius()))
			{
				if (Ships[0]->getHealthCount() > 0)
				{
					Ships[0]->setHealthCount(Ships[0]->getHealthCount() - 1);
					Ships[0]->setX(Board_Width / 2);
					Ships[0]->setY(Board_Height / 2);
					Ships[0]->setAngle(0.0);
					UpdateAsteroids(i);
				}
				else if (Ships[0]->getHealthCount() == 0)
				{
					gameOver = true;
				}
				break;
			}
		}
		CheckNow = false;
	}
	if (isEnemy == true)
	{
		Bullets *bullets;
		int count = 0;
		bullets = Ships[1]->getBulllets();
		count = Ships[1]->getCount();
		for (int i = 0; i < count; i++)
		{

			if (bullets[i].getX() <= Ships[0]->getX())
			{
				Distance = distance(bullets[i].getX(), bullets[i].getY(), Ships[0]->getX(), Ships[0]->getY());
				if (Distance <= (bullets[i].getRadius() + Ships[0]->getRadius()))
				{
					Ships[1]->RemoveBullet(i);
					Ships[0]->setHealthCount(Ships[0]->getHealthCount() - 1);
					Ships[0]->setX(Board_Width / 2);
					Ships[0]->setY(Board_Height / 2);
					Ships[0]->setAngle(0.0);
					Ships[0]->setHealthCount(Ships[0]->getHealthCount() - 1);
				}
			}
		}
		Distance = distance(Ships[0]->getX(), Ships[0]->getY(), Ships[1]->getX(), Ships[1]->getX());
		if (Distance <= (Ships[0]->getRadius() + Ships[1]->getRadius()))
		{
			if (Ships[1]->getName() == "ComplexEnemy")
			{
				Score += 500;
				ScoreCheck += 500;
			}
			if (Ships[1]->getName() == "SimpleEnemy")
			{
				Score += 100;
				ScoreCheck += 100;
			}
			Ships[1]=NULL;
			Ships[0]->setHealthCount(Ships[0]->getHealthCount() - 1);
			Ships[0]->setX(Board_Width / 2);
			Ships[0]->setY(Board_Height / 2);
			Ships[0]->setAngle(0.0);
			Ships[0]->setHealthCount(Ships[0]->getHealthCount() - 1);
			isEnemy = false;
		}
		bullets = NULL;
		if (count > 0)
		{
			delete[]bullets;
		}
		else
		{
			delete bullets;
		}
	}
}

void GameInterface::AddEnemyShips()
{
	if (isEnemy == false)
	{
		shipCount = 2;
		int Loc_X, Loc_Y;
		float velocity_X, velocity_Y;
		Loc_Y = GetRandInRange(10, Board_Height+10);
		int choice = GetRandInRange(0, 1);
		if (choice == 1)
		{
			Loc_X = Board_Width - 20;
			velocity_X = -0.1;
			velocity_Y = 0;
		}
		else if (choice == 0)
		{
			Loc_X = 20;
			velocity_X = 0.1;
			velocity_Y = 0;
		}
		float angle = GetRandInRange(0, 270);
		choice = GetRandInRange(1, 3);
		if (choice == 1)
		{
			Ships[1] = new SimpleEnemy("SimpleEnemy", Loc_X, Loc_Y, ENEMYSHIPRADIUS, velocity_X, velocity_Y,angle);
		}
		else
		{
			Ships[1]=new ComplexEnemy("ComplexEnemy", Loc_X, Loc_Y, ENEMYSHIPRADIUS,0, 0,90);
		}
		isEnemy = true;
	}
}

void GameInterface::ChangeComplexDirections()
{
	ComplexAsteroid *complexAsteroid;
	for (int index_save = 0; index_save < asteroidCount; index_save++)
	{
		if (Asteroids[index_save]->getName() == "Complex")
		{
			complexAsteroid = new ComplexAsteroid(Asteroids[index_save]->getName(), Asteroids[index_save]->getX(),
				Asteroids[index_save]->getY(), Asteroids[index_save]->getRadius(), Asteroids[index_save]->getCorners(),
				Asteroids[index_save]->getVelocityX(), Asteroids[index_save]->getVelocityY(), Asteroids[index_save]->getAngle());

			complexAsteroid->ChangePosition();

			Asteroids[index_save]->setName(complexAsteroid->getName());
			Asteroids[index_save]->setX(complexAsteroid->getX());
			Asteroids[index_save]->setY(complexAsteroid->getY());
			Asteroids[index_save]->setVelocity(complexAsteroid->getVelocityX(), complexAsteroid->getVelocityY());
			Asteroids[index_save]->setRadius(complexAsteroid->getRadius());
			Asteroids[index_save]->setAngle(complexAsteroid->getAngle());
			complexAsteroid = NULL;
			delete complexAsteroid;
		}
	}
	if (isEnemy == true)
	{
		ComplexEnemy *enemy;
		if (Ships[1]->getName() == "ComplexEnemy")
		{
			enemy = new ComplexEnemy(Ships[1]->getName(), Ships[1]->getX(), Ships[1]->getY(),
				Ships[1]->getRadius(), Ships[1]->getVelocityX(), Ships[1]->getVelocityY(), Ships[1]->getAngle());
			
			enemy->ChangeDirection();
			Ships[1]->setName(enemy->getName());
			Ships[1]->setX(enemy->getX());
			Ships[1]->setY(enemy->getY());
			Ships[1]->setVelocityX(enemy->getVelocityX());
			Ships[1]->setVelocityY(enemy->getVelocityY());
			Ships[1]->setAngle(enemy->getAngle());
		}
		enemy = NULL;
		delete enemy;
	}

}

void GameInterface::MovetoNextLevel()
{
	if (asteroidCount == 0 && Ships[1]==NULL)
	{
		delete[]Asteroids;
		isDrawn = false;
		isEnemy = false;
		level += 1;
	}
}

float GameInterface::distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void GameInterface::WrapObjects()
{

	for (int i = 0; i < asteroidCount; i++)
	{
		WrapBoard(*Asteroids[i]);
	}
	for (int i = 0; i < shipCount; i++)
	{
		if (Ships[i] != NULL)
			WrapBoard(*Ships[i]);
	}
}

void GameInterface::EnterHyperSpace(bool Enter)
{
	IntoHyperSpace = true;
}

void GameInterface::StartGame()
{
	if (gameOver == false)
	{
		if (isDrawn == false)
		{
			b->Draw();
			CreateObjects();
			isDrawn = true;
		}
		if (IntoHyperSpace == false)
		{
			DrawObjects();
		}
		else if (IntoHyperSpace == true)
		{
			Ships[0]->Move();
			if (HyperCount == 400)
			{
				IntoHyperSpace = false;
				HyperCount = 0;
				Float = true;
			}
			HyperCount++;
		}
		if (Float == true)
		{
			Ships[0]->Shipfloat();
		}
		MoveObjects();
		ObjectsCollision();
		ShipCollision();
		WrapObjects();
		MoveBullets();
		MovetoNextLevel();
		if (call == callEnemy)
		{
			AddEnemyShips();
			call = 0;
		}
		if (isEnemy == true)
		{
		Ships[1]->Move();
		if (Eshoot == shootInterval)
		{
			Ships[1]->Shoot();
			Eshoot = 0;
		}
		Eshoot++;
		}
		if (ComplexChangeDir == 3000)
		{
			ChangeComplexDirections();
			ComplexChangeDir = 0;
		}
		if (ShipCoolDown == 0)
		{
			if (CheckNow == false)
			{
				CheckNow = true;
			}
			ShipCoolDown = 800;
		}
		ComplexChangeDir += 1;
		ShipCoolDown -= 1;
		call+=1;
		if (ScoreCheck > 4000)
		{
			Ships[0]->setHealthCount(Ships[0]->getHealthCount() + 1);
			ScoreCheck = 0;
		}

		DrawScore = "SCORE : " + to_string(Score);
		DrawLives = "LIVES : " + to_string(Ships[0]->getHealthCount());
		DrawString(text_X, text_Y, DrawScore, colors[5]);
		DrawString(Lives_X, text_Y, DrawLives, colors[5]);
		if (Ships[0]->getHealthCount() <= 0)gameOver = true;
	}
	else if (gameOver == true)
	{
		DrawString(Board_Width / 2 - 50, Board_Height / 2, "GameOVER", colors[5]);
		DrawString(Board_Width / 2 - 50, Board_Height / 2 - 100, DrawScore, colors[5]);
	}
}

