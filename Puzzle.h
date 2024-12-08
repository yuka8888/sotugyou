#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
class Puzzle :public IScene
{
public:

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画面サイズ
	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

	Fade* fade_ = nullptr;

	int puzzleA[4][4] = {{1,1,1,1},
					     {1,0,0,1},
					     {1,0,0,1},
		                 {1,1,1,1} };

	int puzzleB[4][4] = { {1,1,1,1},
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
	int actNum_;
	//画像サイズ
	int textureSize_ = 32;
	//基準の座標
	Vector2 puzzlePos_ = { 100,100 };
	int selectPos_[4][4];
	int selectPosX_;
	int selectPosY_;
	bool isMatch_[4][4];
	};


