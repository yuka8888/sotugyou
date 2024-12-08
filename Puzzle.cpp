#include "Puzzle.h"

void Puzzle::Initialize()
{
}

void Puzzle::Update()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
	SelectPosUpd();
	InvertPanel();
	selectPos_[selectPosX_][selectPosY_] = 1;
}

void Puzzle::Draw()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (puzzleA[i][j] == 1) {
				Novice::DrawBox(int(puzzlePos_.x + textureSize_ * i), int(puzzlePos_.x + textureSize_ * j), int(textureSize_), int(textureSize_), 0.0f, RED, kFillModeSolid);
			}
			else {
				Novice::DrawBox(int(puzzlePos_.x + textureSize_ * i), int(puzzlePos_.x + textureSize_ * j), int(textureSize_), int(textureSize_), 0.0f, WHITE, kFillModeSolid);
			}
		}
	}



	Novice::DrawBox(int(puzzlePos_.x + textureSize_ * selectPosX_), int(puzzlePos_.y + textureSize_ * selectPosY_), textureSize_, textureSize_, 0.0f, BLACK, kFillModeWireFrame);

}

void Puzzle::CheckPuzzle()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (puzzleA[i][j] == puzzleB[i][j]) {
				isMatch_[i][j] = true;
			}
		}
	}

}

void Puzzle::SelectPosUpd()
{


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
	if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {


	}

}
