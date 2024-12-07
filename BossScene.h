#pragma once
#include "Boss.h"


class BossScene
{
public:
	BossScene();

	~BossScene();

	void Initialize();

	void Update();

	void Draw();

private:
	Boss* boss_;

	const float kGround_ = 600.0f;


};

