#pragma once
class Enemy
{
private:
	int enemyPosX;
	int enemyPosY;
	int enemySpeed;
	int gameOver = 0;
	int timer = 20;
public:
	Enemy();

	int enemyGetPosX() const { return enemyPosX; }
	int enemyGetPosY() const { return enemyPosY; }

	void Draw();

	void move();

	void Initalize();
};