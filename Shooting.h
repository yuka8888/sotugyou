#pragma once
#include "mt.h"
#include "Novice.h"
#include "time.h"
#include "Bullet.h"
#include "Enemy.h"

class Player;
class Shooting
{
public:
	~Shooting();

	void Initialize();

	void Update();

	void Draw();

	void SetPlayer(Player* player);

private:
	Player* player_ = nullptr;

	static const int kEnemyNum = 10;

	Enemy* enemy_[kEnemyNum];
	
};

