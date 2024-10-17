#pragma once
#include "IScene.h"
#include "Novice.h"
#include "Fade.h"
#include "Player.h"


class PlayScene :public IScene
{
public:
	PlayScene();

	~PlayScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

private:
	//ゲームのフェーズ
	enum class Phase {
		kMovePlayerGirlTop, //女の子が上で動く
		kMovePlayerBoyTop, //男の子が上で動く
		kMovePlayerGirlBottom, //女の子が下で動く
		kMovePlayerBoyBottom, //男の子が下で動く
		kMoveAll, //どっちも動く
	};

	Fade* fade_ = nullptr;

	Player* player_ = nullptr;

	//現在のフェーズ
	Phase phase = Phase::kMovePlayerGirlTop;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;


};