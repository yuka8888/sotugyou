
#include "ClearScene.h"

ClearScene::ClearScene()
{
	delete fade_;
}

void ClearScene::Initialize()
{
	fade_ = new Fade;
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
	backGroundTexture_ = Novice::LoadTexture("./Resources/GameClear.png");
	
}

void ClearScene::Update()
{
	fade_->Update();

	if (Novice::CheckHitKey(DIK_SPACE) && fade_->IsFinished() &&!(fade_->GetStatus() == Fade::Status::FadeOut)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
		sceneNo = kTitle;
	}

}

void ClearScene::Draw()
{
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, WHITE, kFillModeSolid);
	fade_->Draw();
}