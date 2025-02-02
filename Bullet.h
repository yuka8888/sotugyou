#pragma once
#include "mt.h"
#include "Novice.h"

class Bullet
{
public:
	Bullet();

	void Initialize();

	void BossInitialize();

	void PlayerInitialize();

	void SlimeInitialize();

	void Update();

	void BossUpdate();

	void Draw();

	void Shot();

	void IsAttack(bool isAttack);
	bool IsAttack();

	bool IsCollision();
	void IsCollision(bool isCollision);

	void SetPosition(Vector2 position);

	void SetDirection(Direction direction);

	AABB GetAABB();

private:
	bool isAttack_ = false;

	Vector2 position_ = {};

	Vector2 size_ = { 16.0f, 16.0f };

	Vector2 velocity_ = {};

	Direction direction_ = Direction::kLeft;

	AABB aabb_ = {};

	float theta_ = 0.0f;

	bool isCollision_ = false;

	int bulletTexture_;
};

