#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include "Player.h"
#include "MapChipManager.h"
#include "ActionGame.h"
#include "BossScene.h"
#include "time.h"

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

	BossScene* bossScene_;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画面サイズ
	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

	Fade* fade_ = nullptr;

	Player* player_ = nullptr;

	ActionGame* actionGame_ = nullptr;

	//現在のフェーズ
	Phase phase_ = Phase::dice;

	MapChipManager* mapChipManager_ = nullptr;

	int random_ = 0;

	//すごろく関連
	//進める道の個数
	uint32_t pathsNum_ = 0;

	//進める場所の記録
	Direction paths_[4] = {};

	//前回進んだ方向
	Direction prePaths_ = Direction::kRight;

	//残り進める数
	uint32_t dice_ = 0;

	//すごろくで使うタイマー
	float sugorokuTimer = 0.0f;

	//すごろくのマスの大きさ
	float kBlockWidth = 0;
	float kBlockHeight = 0;

	//道を選んでいるときか
	bool isChoicePaths_ = false;

	//サイコロを振っているか
	bool isRollDice = false;

	unsigned int currentTime;

	bool isGoal = false;

	//テクスチャ
	int startBlockTexture_;
	int goalBlockTexture_;
	int noneBlockTexture_;
	int puzzleBlockTexture_;

	int rouletteTexture_;
	int backGroundTexture_;

	//関数
	//マップを描画
	void DrawMap();

	/// <summary>
	/// サイコロを振る
	/// </summary>
	void RollTheDice();

	/// <summary>
	/// フェースの切り替え
	/// </summary>
	void ChangePhase();

};