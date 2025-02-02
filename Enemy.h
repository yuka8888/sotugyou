#pragma once
#include "mt.h"
#include "time.h"
#include "random"
#include "Novice.h"
#include "Bullet.h"

class Enemy
{
public:
	void Initialize();

	void Update();

	void Draw();

	void SetPlayerPosition(Vector2 playerPosition);

	Type GetType();

	void IsStart(bool isStart);
	bool IsStart();

	void IsCollision(bool isCollision);
	bool IsCollision();

	void IsBulletCollision(bool isBulletCollision, int i);
	bool IsBulletCollision(int i);

	bool isBulletAttack(int i);

	bool IsNothing();

	bool IsDeath();

	int GetBulletNum();

	AABB GetBulletAABB(int i);

	void IsDeath(bool isDeath);

	AABB GetAABB();

private:
	Vector2 position_ = {};

	Direction direction_ = Direction::kUp;

	Vector2 velocity_ = {};
	Vector2 size_ = { 32.0f, 32.0f };

	AABB aabb_ = {};

	Vector2 playerPosition_ = {};

	unsigned int currentTime_;

	bool isStart_ = false;

	bool isAttack = false;

	bool isDeath_ = false;

	bool isNothing = true;

	bool isCollision_ = false;

	float attackTimer_ = 0.0f;

	static const int kBulletNum = 6;

	Bullet* bullet_[kBulletNum];

	//攻撃タイプ
	Type type_ = Type::kNormal;

	void Move();

	int normalTexture;
	int trackingTexture;
	int rushTexture;
};

