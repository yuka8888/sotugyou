#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Initialize()
{
	currentTime = (unsigned int)time(nullptr);
	srand(currentTime);
	translation_.y = kGround_ - kHeight_ / 2.0f;
}

void Boss::Update()
{
	//移動
	Move();
}

void Boss::Draw()
{
	Novice::DrawBox(int(translation_.x - kWidth_ / 2.0f), int(translation_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, RED,kFillModeSolid);
}

void Boss::SetGround(float kGround)
{
	kGround_ = kGround;
}

void Boss::Move()
{
	moveTimer_ += 0.1f;


	//左右の移動を一定時間でランダムに変える
	if (moveTimer_ >= 10.0f) {
		random = rand() / 2;
		moveTimer_ = 0.0f;
	}

	if (random == 0) {
		velocity_.x = 3.0f;
	}
	else {
		velocity_.x = -3.0f;
	}

	translation_ = translation_ +  velocity_;
}

