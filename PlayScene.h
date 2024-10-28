#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include "Player.h"
#include "MapChipManager.h"

class PlayScene :public IScene
{
public:
	PlayScene();

	~PlayScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:
	//ゲームのフェーズ
	enum class Phase {
		dice, //すごろく
		miniGame, //ミニゲーム
		boss, // ボス
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Fade* fade_ = nullptr;

	Player* player_ = nullptr;

	//現在のフェーズ
	Phase phase_ = Phase::dice;

	MapChipManager* mapChipManager_ = nullptr;

	int dice = 0;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

	//すごろくのマスの大きさ
	float kBlockWidth = 0;
	float kBlockHeight = 0;

	void DrawMap();

};