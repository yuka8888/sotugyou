#include "TitleScene.h"

TitleScene::TitleScene()
{
	delete fade_;
}

void TitleScene::Initialize()
{

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	backGroundTexture_ = Novice::LoadTexture("./Resources/Title.png");
}

void TitleScene::Update()
{
	fade_->Update();

	if (Novice::CheckHitKey(DIK_SPACE) && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
		sceneNo = kPlay;
	}

}

void TitleScene::Draw()
{
	Novice::DrawSprite(0, 0, backGroundTexture_, 1.0f, 1.0f, 0.0f, WHITE);

	fade_->Draw();
}