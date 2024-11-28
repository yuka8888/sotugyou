#pragma once
#include "mt.h"
#include "Player.h"

class ActionGame
{
public:
	void Initialize();

	void Update();

	void Draw();

	bool IsClear();

	//ゴールの場所
	Vector2 actionGoalPosition = { 700.0f, (float)kGroundPosition };

	Vector2 actionGoalSize = { 50.0f, 50.0f };

	AABB actionGoalAABB;

private:
	Player* player_ = nullptr;

	//クリアしたか
	bool isClear_ = false;

};