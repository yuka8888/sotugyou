#pragma once
#include "Novice.h"
#include"mt.h"
class Puzzle
{
public:

	void Initialize();

	void Update();

	void Draw();

	bool IsClear();

	bool IsGameOver();

private:


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画面サイズ
	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;



	int correctPuzzle[4][4] = { {1,1,1,1},
						 {1,0,0,1},
						 {1,0,0,1},
						 {1,1,1,1} };

	int changePuzzle[4][4] = { {1,1,1,1},
						  {1,0,0,1},
						  {1,0,1,0},
						  {1,1,0,0} };

	//手本と合っているか
	void CheckPuzzle();
	//選択位置
	void SelectPosUpd();
	//動かす
	void InvertPanel();
	//動かせる回数
	int actNum_ = 3;
	//画像サイズ
	float textureSize_ = 64;
	//基準の座標
	Vector2 correctPuzzlePos_ = { 300,200 };
	Vector2 changePuzzlePos_ = { 650,200 };

	//選択したパネルの位置を記憶
	int selectPos_[4][4];
	int selectPosX_ = 0;
	int selectPosY_ = 0;
	//パネルが合っているか
	bool isMatch_[4][4];
	//ゲームクリアフラグ
	bool isClear_;
	//ゲームオーバーフラグ
	bool isGameOver_;

	//画像
	int sakuraTexture_ = Novice::LoadTexture("./Resources/sakura.png");
	int cherryTexture_ = Novice::LoadTexture("./Resources/cherry.png");
	int frameTexture_ = Novice::LoadTexture("./Resources/frame.png");
	int bgTexture_ = Novice::LoadTexture("./Resources/puzzle_bg.png");

};

