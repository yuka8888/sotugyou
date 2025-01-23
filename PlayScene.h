#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include "Player.h"
#include"ShootingPlayer.h"
#include "ShootingEnemyManager.h"
#include "ShootingItemManager.h"

class PlayScene : public IScene
{
public:
	PlayScene();
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	enum class Phase 
	{
		dice,        // すごろく
		miniGame,    // ミニゲーム
		boss         // ボス
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Fade* fade_ = nullptr;
	Player* player_ = nullptr;
	ShootingPlayer* shootingPlayer_ = nullptr;
	ShootingEnemyManager* enemyManager_ = nullptr;
	ShootingItemManager* itemManager_ = nullptr;

	Phase phase_ = Phase::dice; // 現在のフェーズ

	int dice = 0;
	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

	// マップ関連
	float kBlockWidth = 0;
	float kBlockHeight = 0;

	void DrawMap();
	bool Collision(Vector2 playerPos, Vector2 enemyPos, float playerRadius, float enemyRadius);
};
