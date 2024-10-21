#include "PlayScene.h"

PlayScene::PlayScene()
{
	delete fade_;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	player_ = new Player;
	player_->Initialize();
}

void PlayScene::Update()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	fade_->Update();

	switch (phase) {
		case Phase::dice:
			player_->dicePhaseUpdate();

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				dice = rand() % 6 + 1;
			}
			break;
		case Phase::miniGame:
			break;
		case Phase::boss:
			break;
	}

	if (Novice::CheckHitKey(DIK_SPACE) && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
		sceneNo = kClear;
	}

}

void PlayScene::Draw()
{
	player_->Draw();
	fade_->Draw();
}