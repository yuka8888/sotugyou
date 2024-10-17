#include "Player.h"

void Player::Initialize()
{
}

void Player::Update()
{
	Move();
	translation_ = translation_ + velocity_;
}

void Player::Draw()
{
	Novice::DrawBox(int(translation_.x - kWidth_ / 2.0f), int(translation_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, BLUE, kFillModeSolid);

}

void Player::Move()
{
	velocity_ = {};

	if (Novice::CheckHitKey(DIK_A) || Novice::CheckHitKey(DIK_LEFTARROW)) {
		direction_ = Direction::kLeft;
		velocity_.x = -2.0f;
	}
	else if (Novice::CheckHitKey(DIK_D) || Novice::CheckHitKey(DIK_RIGHTARROW)) {
		direction_ = Direction::kRight;
		velocity_.x = 2.0f;
	}
}
