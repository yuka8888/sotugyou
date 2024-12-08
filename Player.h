#pragma once
#include "Novice.h"
#include "mt.h"

class MapChipManager;

class Player
{
public:
	void Initialize();

	void dicePhaseUpdate();

	void ActionGameUpdate();

	void Draw();

	void SetTranslation(Vector2 translation);

	void SetPaths(Direction paths);

	void SetMapChipPosition(IndexSet index);

	IndexSet GetMapChipPosition();

	void SetMapChipManager(MapChipManager* mapChipManager);

	AABB GetAABB();

	void SetAttack(int attack);

	void SetHp(int hp);

	void SetDefense(int defense);

	int GetAttack();

	int GetHp();

	int GetDefense();

private:
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	MapChipManager* mapChipManager_ = nullptr;

	Vector2 translation_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Vector2 acceleration_ = {};

	AABB aabb_;

	float kGround_ = 600.0f;

	bool isGround_ = true;

	Direction direction_ = Direction::kLeft;

	Direction paths_ = Direction::kNone;

	float kWidth_ = 36.0f;

	float kHeight_ = 36.0f;

	//ボス戦で使うステータス
	//攻撃力
	int attack_ = 1;

	//防御力
	int defense_ = 1;

	//HP
	int hp_ = 5;

	//プレイヤーのマップチップでの座標
	IndexSet mapChipPosition_;

	//サイコロの目
	int dice_ = 0;

	//アクションゲーム関連
	//ジャンプしているか
	bool isJump = false;
	bool isAlive_ = true;
	/// <summary>
	/// 移動
	/// </summary>
	void Move();


};

