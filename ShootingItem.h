#pragma once
#pragma once
#include "Vector2.h"

class Item
{
private:
	Vector2 pos_;       // 位置
	int radius_;        // 半径
	bool isAlive_;      // 生存フラグ（存在するかどうか）

public:
	Item();
	void Initialize(Vector2 spawnPos);
	void Update();
	void Draw() const;
	void SetAlive(bool isAlive) { isAlive_ = isAlive; }
	bool GetAlive() const { return isAlive_; }
	Vector2 GetPos() const { return pos_; }
	int GetRadius() const { return radius_; }
	bool CheckCollision(Vector2 playerPos, int playerRadius) const;
};
