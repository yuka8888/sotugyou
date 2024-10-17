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
}

void TitleScene::Update()
{
	fade_->Update();

	if (Novice::CheckHitKey(DIK_SPACE) && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
		sceneNo = kPlay;
	}

}

void TitleScene::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLUE, kFillModeSolid);

	fade_->Draw();
}