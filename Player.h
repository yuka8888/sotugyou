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

	void BossDraw();

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

	int GetMaxHp();

	void SetMaxHp(int maxHp);

	AABB GetBulletAABB(int i);

	Vector2 GetPosition();

	void IsCollision(bool isCollision_);

	bool IsPreCollision();

	bool IsBulletCollision(int i);
	void IsBulletCollision(bool isBulletCollision, int i);

	bool IsBulletDraw(int i);
	void IsBulletDraw(bool isBulletDraw, int i);

	int GetBulletNum();

	int GetAttackUpNum_();

	void SetAttackUpNum_(int attackUpNum);

	void AnimationTimer();
private:
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MapChipManager* mapChipManager_ = nullptr;

	Vector2 position_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Vector2 acceleration_ = {};

	AABB aabb_ = {};

	bool isGround_ = true;

	bool isPreCollision_ = false;

	bool isCollision_ = false;

	Direction direction_ = Direction::kRight;

	Direction paths_ = Direction::kNone;

	float kWidth_ = 64.0f;

	float kHeight_ = 64.0f;

	float speed_ = 5.0f;

	//アクションゲームで使うステータス
	//攻撃力
	int attack_ = 1;

	//HP
	int hp_ = 5;
	int maxHp_ = 5;

	//攻撃しているか
	bool isAttack_ = false;

	//攻撃
	static const int kBulletNum = 20;
	Bullet* bullet_[kBulletNum];

	//攻撃用のタイマー
	float attackTimer_ = 0.0f;

	float coolTime_ = 2.0f;

	bool isStrongAttack_ = false;

	//プレイヤーのマップチップでの座標
	IndexSet mapChipPosition_;

	//サイコロの目
	int dice_ = 0;

	//ジャンプしているか
	bool isJump_ = false;

	int playerShootingTexture_;

	int attackUpNum_ = 0;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

	void BossMove();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	void BossAttack();

	//画像
	int playerRightTexture_ = Novice::LoadTexture("./Resources/player_action_right.png");
	int playerLeftTexture_ = Novice::LoadTexture("./Resources/player_action_left.png");
	//画像のタイマー
	float textureTimer_ = 0;

};

