
#pragma once
#include "IScene.h"
#include "Fade.h"
#include <Input.h>

class TitleScene :public IScene
{
public:

	enum class Phase
	{
		kFadeIn,
		kMain,
		kFadeOut,
	};

	TitleScene();

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

	//終了フラグ
	bool finished_ = false;
};