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
	fade_->Update();

	player_->Update();

	if (Novice::CheckHitKey(DIK_SPACE) && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
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