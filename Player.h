#pragma once
#include "Novice.h"
#include "mt.h"
#include "Bullet.h"

class MapChipManager;

class Player
{
public:
	~Player();

	void Initialize();

	void dicePhaseUpdate();

	void ActionGameUpdate();

	void BossUpdate();

	void Draw();

	void SetPosition(Vector2 translation);

	void SetPaths(Direction paths);

	void SetMapChipPosition(IndexSet index);

	IndexSet GetMapChipPosition();

	void SetMapChipManager(MapChipManager* mapChipManager);

	AABB GetAABB();

	void SetAttack(int attack);

	void SetHp(int hp);

	int GetAttack();

	int GetHp();

	AABB GetBulletAABB();

	Vector2 GetPosition();

	void IsCollision(bool isCollision_);

	bool IsPreCollision();

private:
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MapChipManager* mapChipManager_ = nullptr;

	Vector2 position_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Vector2 acceleration_ = {};

	AABB aabb_;

	bool isGround_ = true;

	bool isPreCollision_ = false;

	bool isCollision_ = false;

	Direction direction_ = Direction::kLeft;

	Direction paths_ = Direction::kNone;

	float kWidth_ = 36.0f;

	float kHeight_ = 36.0f;

	//アクションゲームで使うステータス
	//攻撃力
	int attack_ = 1;

	//HP
	int hp_ = 5;

	//攻撃しているか
	bool isAttack_ = false;

	//攻撃
	Bullet* bullet_ = nullptr;

	//攻撃用のタイマー
	float attackTimer_ = 0.0f;

	//プレイヤーのマップチップでの座標
	IndexSet mapChipPosition_;

	//サイコロの目
	int dice_ = 0;

	//ジャンプしているか
	bool isJump_ = false;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
};

