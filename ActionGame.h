#pragma once
#include "mt.h"
#include "Novice.h"
#include "time.h"
#include "imgui.h"
#include "Bullet.h"

class ActionGame
{
public:
	ActionGame();

	~ActionGame();

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

	bool IsClear();

	void AnimationTimer();

private:
	//弾
	Bullet* bullet_ = nullptr;

	Direction direction_ = Direction::kLeft;

	const float kWidth_ = 64.0f;

	const float kHeight_ = 64.0f;

	//攻撃しているか
	bool isAttack_ = false;

	//攻撃するタイミングのタイマー
	float attackTimer_ = 0.0f;

	//体力
	int hp_ = 100;

	AABB aabb = {};

	Vector2 position_ = {};

	Vector2 velocity_ = {};

	float moveTimer_ = 5.0f;

	unsigned int currentTime_ = 0;

	bool isClear_ = false;

	bool isCollision_ = false;
	bool isPreCollision_ = false;

	//プレイヤーの座標
	Vector2 playerPosition_ = {};

	int random_ = 0;

	//無敵時間かどうか
	bool isInvincibleTime_ = false;

	//無敵時間のタイマー
	float invincibleTimer_ = 0.0f;

	//関数系
	void Move();

	//画像
	int slimeRightTexture_ = Novice::LoadTexture("./Resources/slime_right.png");
	int slimeLeftTexture_ = Novice::LoadTexture("./Resources/slime_left.png");
	//画像のタイマー
	float textureTimer_ = 0;
};