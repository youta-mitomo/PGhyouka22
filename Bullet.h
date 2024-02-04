#pragma once
#include "Player.h"

class Bullet
{
private:
	int bulletPosX;
	int bulletPosY;
	int bulletSpeed;
	bool bulletFlag = 0;
public:

	Bullet();
	void SetPosition(int x, int y);

	void Initalize();

	int bulletGetX() const { return bulletPosX; }
	int bulletGetY() const { return bulletPosY; }

	void Draw();
	void shot(char keys[], char preKeys[], int x, int y);

	Player player;
};
