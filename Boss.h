#pragma once
#include "mt.h"
#include "Novice.h"
#include "time.h"
#include "Bullet.h"

class Boss
{
public:
	Boss();

	~Boss();

	void Initialize();

	void Update();

	void Draw();

	AABB GetAABB();

	AABB GetBulletAABB();

	void SetHp(int hp);

	int GetHp();

	void IsCollision(bool isCollision);

	bool IsPreCollision();

	//無敵時間と攻撃を受けるときの切り替え
	void SwitchState();

	//攻撃
	void Attack();

	void SetPlayerPosition(Vector2 playerPosition);

private:
	//弾
	Bullet *bullet_ = nullptr;

	Direction direction_ = Direction::kLeft;

	const float kWidth_ = 32.0f;

	const float kHeight_ = 64.0f;

	bool isCollision_ = false;
	bool isPreCollision_ = false;

	//攻撃しているか
	bool isAttack_ = false;

	//攻撃するタイミングのタイマー
	float attackTimer_ = 0.0f;

	//体力
	int hp_ = 100;

	AABB aabb = {};

	Vector2 position_ = {};

	Vector2 velocity_ = {};

	float moveTimer_ = 0;

	unsigned int currentTime_ = 0;

	//プレイヤーの座標
	Vector2 playerPosition_ = {};

	int random_ = 0;

	//無敵時間かどうか
	bool isInvincibleTime_ = false;

	//無敵時間のタイマー
	float invincibleTimer_ = 0.0f;

	//関数系
	void Move();

};

