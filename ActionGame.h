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
	Vector2 actionGoalPosition = { 700.0f, (float)kGroundPosition-300 };

	Vector2 actionGoalSize = { 50.0f, 50.0f };

	Vector2 actionScaffoldPosition[3];
	Vector2 actionScaffoldSize = { 80.0f ,25.0f };

	AABB actionGoalAABB;
	AABB actionScaffoldAABB[3];
private:
	Player* player_ = nullptr;

	//クリアしたか
	bool isClear_ = false;


};