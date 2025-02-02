#pragma once
#include "mt.h"
#include "Novice.h"

class Bullet
{
public:
	Bullet();

	void Initialize();

	void PlayerInitialize();

	void SlimeInitialize();

	void Update();

	void Draw();

	void Shot();

	void SetIsAttack(bool isAttack);

	void SetPosition(Vector2 position);

	void SetDirection(Direction direction);

	AABB GetAABB();



private:
	bool isAttack_ = false;

	Vector2 position_ = {};

	Vector2 size_ = {};

	Vector2 velocity_ = {};

	Direction direction_ = Direction::kLeft;

	AABB aabb_ = {};

	int bulletTexture_;
};

