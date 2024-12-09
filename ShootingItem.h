#pragma once
#pragma once
#include "Vector2.h"

class Item
{
private:
	Vector2 pos_;       // �ʒu
	int radius_;        // ���a
	bool isAlive_;      // �����t���O�i���݂��邩�ǂ����j

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
