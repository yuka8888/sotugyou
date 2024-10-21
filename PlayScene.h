#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include "Player.h"


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
	Phase phase = Phase::dice;

	int dice = 0;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;


};