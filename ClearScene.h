#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include"Vector2.h"

class ClearScene :public IScene
{
public:
	ClearScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	Fade* fade_ = nullptr;

	//背景の幅
	int kWidth_ = 720;
	int kHeight_ = 360;
	int kMostPos_ = 1280;
	Vector2 kBackPos_ = { 640.0f , 355.0f };

};