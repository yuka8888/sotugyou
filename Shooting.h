#pragma once
#include "mt.h"
#include "Novice.h"
#include "time.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"

class Player;
class Shooting
{
public:
	~Shooting();

	void Initialize();

	void Update();

	void Draw();

	void SetPlayer(Player* player);

	bool IsClear();

	bool IsGameOver();

private:
	Player* player_ = nullptr;

	Boss* boss_ = nullptr;

	static const int kEnemyNum = 15;

	Enemy* enemy_[kEnemyNum];

	float spawnTimer = 0.0f;

	bool isClear_ = false;

	bool isGameOver_ = false;

	void Collision();

	Vector2 bgPosition = {};
	Vector2 bgPosition2 = {1280.0f, 0};

	int backGroundTexture_;
};

