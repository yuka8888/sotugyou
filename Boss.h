#pragma once
#include "mt.h"
#include "Novice.h"
#include"Bullet.h"

class Boss
{
public:
	~Boss();

	void Initialize();

	void Update();

	void Draw();

	void SetHp(int hp);

	int GetHp();

	AABB GetAABB();

	int GetBulletNum();

	AABB GetBulletAABB(int i);

	bool IsBulletCollision(int i);
	void IsBulletCollision(bool isBulletCollision, int i);

	bool IsBulletAttack(int i);

	bool IsAlive();

private:
	Vector2 position_ = { 1400.0f, 360.0f };

	Vector2 velocity_ = {};

	Vector2 size_ = { 144.0f, 122.0f };

	static const int kBulletNum_ = 20;

	Bullet* bullet_[kBulletNum_];

	int bossTexture_;

	int hp_ = 20;

	AABB aabb_;

	bool isAlive_ = true;

	float theta_ = 0.0f;

	float attackTimer_ = 0.0f;

	void Shot();

};

