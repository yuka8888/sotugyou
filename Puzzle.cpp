#include "Puzzle.h"
void Puzzle::Initialize()
{
	isClear_ = false;
	isGameOver_ = false;
}

void Puzzle::Update()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	SelectPosUpd();
	InvertPanel();
	CheckPuzzle();
	selectPos_[selectPosX_][selectPosY_] = 1;

}

void Puzzle::Draw()
{
	//背景描画
	Novice::DrawSprite(0, 0, bgTexture_, 1.0f, 1.0f, 0.0f, WHITE);

	//お手本描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (correctPuzzle[i][j] == 1) {

				Novice::DrawSprite(int(correctPuzzlePos_.x + textureSize_ * i), int(correctPuzzlePos_.y + textureSize_ * j), sakuraTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			else {

				Novice::DrawSprite(int(correctPuzzlePos_.x + textureSize_ * i), int(correctPuzzlePos_.y + textureSize_ * j), cherryTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
		}
	}
	//プレイパズル描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (changePuzzle[i][j] == 1) {

				Novice::DrawSprite(int(changePuzzlePos_.x + textureSize_ * i), int(changePuzzlePos_.y + textureSize_ * j), sakuraTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			else {

				Novice::DrawSprite(int(changePuzzlePos_.x + textureSize_ * i), int(changePuzzlePos_.y + textureSize_ * j), cherryTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Novice::ScreenPrintf(500 + 15 * i, 500 + 15 * j, "%d", correctPuzzle[i][j]);
		}
	}
	//選択のフレーム描画
	Novice::DrawSprite(int(changePuzzlePos_.x + textureSize_ * selectPosX_), int(changePuzzlePos_.y + textureSize_ * selectPosY_), frameTexture_, 1.0f, 1.0f, 0.0f, WHITE);

	Novice::ScreenPrintf(10, 10, "%d", isClear_);
	Novice::ScreenPrintf(10, 30, "%d", isGameOver_);
	Novice::ScreenPrintf(10, 60, "%d", actNum_);
}

bool Puzzle::IsClear()
{
	return isClear_;
}

bool Puzzle::IsGameOver()
{
	return isGameOver_;
}

void Puzzle::CheckPuzzle()
{
	//手本と合っているか調べる
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (correctPuzzle[i][j] == changePuzzle[i][j]) {
				isMatch_[i][j] = true;
			}
			else {
				isMatch_[i][j] = false;
			}
		}
	}

	//すべて一致していたらクリア
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (isMatch_[i][j] == true) {

				isClear_ = true;
			}
			else {
				isClear_ = false;
				break;
			}
		}
	}

	//残り回数が0かつクリアがfalseならゲームオーバーにする
	if (actNum_ <= 0 && isClear_ == false) {
		isGameOver_ = true;
	}
}

void Puzzle::SelectPosUpd()
{

	//選択位置を動かす
	if (keys[DIK_A] && preKeys[DIK_A] == 0) {

		selectPosX_ -= 1;
		if (selectPosX_ <= 0) {
			selectPosX_ = 0;
		}

	}
	if (keys[DIK_D] && preKeys[DIK_D] == 0) {
		selectPosX_ += 1;
		if (selectPosX_ >= 3) {
			selectPosX_ = 3;
		}
	}
	if (keys[DIK_W] && preKeys[DIK_W] == 0) {
		selectPosY_ -= 1;
		if (selectPosY_ <= 0) {
			selectPosY_ = 0;
		}
	}
	if (keys[DIK_S] && preKeys[DIK_S] == 0) {
		selectPosY_ += 1;
		if (selectPosY_ >= 3) {
			selectPosY_ = 3;
		}
	}
}

void Puzzle::InvertPanel()
{

	if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0 && actNum_ > 0) {
		//残り回数を減らす
		actNum_ = actNum_ - 1;

		//選択したパネルを裏返す
		if (changePuzzle[selectPosX_][selectPosY_] == 1) {
			changePuzzle[selectPosX_][selectPosY_] = 0;
		}
		else {
			changePuzzle[selectPosX_][selectPosY_] = 1;
		}

		//以下選択したパネルの周りを裏返す処理
		// 
		//左上
		if (selectPosX_ - 1 >= 0 && selectPosY_ - 1 >= 0) {

			if (changePuzzle[selectPosX_ - 1][selectPosY_ - 1] == 1) {

				changePuzzle[selectPosX_ - 1][selectPosY_ - 1] = 0;
			}
			else if (changePuzzle[selectPosX_ - 1][selectPosY_ - 1] == 0) {

				changePuzzle[selectPosX_ - 1][selectPosY_ - 1] = 1;
			}
		}
		//上
		if (selectPosX_ >= 0 && selectPosY_ - 1 >= 0) {

			if (changePuzzle[selectPosX_][selectPosY_ - 1] == 1) {

				changePuzzle[selectPosX_][selectPosY_ - 1] = 0;
			}
			else if (changePuzzle[selectPosX_][selectPosY_ - 1] == 0) {

				changePuzzle[selectPosX_][selectPosY_ - 1] = 1;
			}
		}

		//右上
		if (selectPosX_ + 1 <= 3 && selectPosY_ - 1 >= 0) {

			if (changePuzzle[selectPosX_ + 1][selectPosY_ - 1] == 1) {

				changePuzzle[selectPosX_ + 1][selectPosY_ - 1] = 0;
			}
			else if (changePuzzle[selectPosX_ + 1][selectPosY_ - 1] == 0) {

				changePuzzle[selectPosX_ + 1][selectPosY_ - 1] = 1;
			}
		}


		//左
		if (selectPosX_ - 1 >= 0) {

			if (changePuzzle[selectPosX_ - 1][selectPosY_] == 1) {

				changePuzzle[selectPosX_ - 1][selectPosY_] = 0;
			}
			else if (changePuzzle[selectPosX_ - 1][selectPosY_] == 0) {

				changePuzzle[selectPosX_ - 1][selectPosY_] = 1;
			}
		}
		//右
		if (selectPosX_ + 1 <= 3) {

			if (changePuzzle[selectPosX_ + 1][selectPosY_] == 1) {

				changePuzzle[selectPosX_ + 1][selectPosY_] = 0;
			}
			else if (changePuzzle[selectPosX_ + 1][selectPosY_] == 0) {

				changePuzzle[selectPosX_ + 1][selectPosY_] = 1;
			}
		}

		//左下
		if (selectPosX_ - 1 >= 0 && selectPosY_ + 1 <= 3) {

			if (changePuzzle[selectPosX_ - 1][selectPosY_ + 1] == 1) {

				changePuzzle[selectPosX_ - 1][selectPosY_ + 1] = 0;
			}
			else if (changePuzzle[selectPosX_ - 1][selectPosY_ + 1] == 0) {

				changePuzzle[selectPosX_ - 1][selectPosY_ + 1] = 1;
			}
		}
		//下
		if (selectPosX_ >= 0 && selectPosY_ + 1 <= 3) {

			if (changePuzzle[selectPosX_][selectPosY_ + 1] == 1) {

				changePuzzle[selectPosX_][selectPosY_ + 1] = 0;
			}
			else if (changePuzzle[selectPosX_][selectPosY_ + 1] == 0) {

				changePuzzle[selectPosX_][selectPosY_ + 1] = 1;
			}
		}

		//右下
		if (selectPosX_ + 1 <= 3 && selectPosY_ + 1 <= 3) {

			if (changePuzzle[selectPosX_ + 1][selectPosY_ + 1] == 1) {

				changePuzzle[selectPosX_ + 1][selectPosY_ + 1] = 0;
			}
			else if (changePuzzle[selectPosX_ + 1][selectPosY_ + 1] == 0) {

				changePuzzle[selectPosX_ + 1][selectPosY_ + 1] = 1;
			}
		}

	}

}
