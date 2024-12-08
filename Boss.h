#pragma once
#include "mt.h"
#include "Novice.h"
#include "time.h"

class Boss
{
public:
	Boss();

	~Boss();

	void Initialize();

	void Update();

	void Draw();

	AABB GetAABB();


private:

	const float kWidth_ = 32.0f;

	const float kHeight_ = 64.0f;

	//攻撃しているか
	bool isAttack_ = false;

	//体力
	int hp_ = 100;

	AABB aabb = {};

	Vector2 translation_ = {};

	Vector2 velocity_ = {};

	float moveTimer_ = 0;

	unsigned int currentTime;

	int random = 0;

	//関数系
	void Move();

};

