#include "BossScene.h"

BossScene::BossScene()
{
}

BossScene::~BossScene()
{
}

void BossScene::Initialize()
{
	boss_ = new Boss;
	boss_->SetGround(kGround_);
	boss_->Initialize();

}

void BossScene::Update()
{
	boss_->Update();
}

void BossScene::Draw()
{
	boss_->Draw();
}
