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
	translation_.y = kGroundPosition - kHeight_ / 2.0f;
	translation_.x = 400.0f;
	aabb.max = { translation_.x + kWidth_ / 2.0f, translation_.y + kHeight_ / 2.0f };
	aabb.min = { translation_.x - kWidth_ / 2.0f, translation_.y - kHeight_ / 2.0f };
}

void Boss::Update()
{
	//AABBの計算
	aabb.max = { translation_.x + kWidth_ / 2.0f, translation_.y + kHeight_ / 2.0f };
	aabb.min = { translation_.x - kWidth_ / 2.0f, translation_.y - kHeight_ / 2.0f };

	//移動
	Move();
}

void Boss::Draw()
{
	Novice::DrawBox(int(translation_.x - kWidth_ / 2.0f), int(translation_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, RED,kFillModeSolid);
}

AABB Boss::GetAABB()
{
	return aabb;
}

void Boss::Move()
{
	moveTimer_ += 0.1f;


	//左右の移動を一定時間でランダムに変える
	if (moveTimer_ >= 10.0f) {
		random = rand() % 2;
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

