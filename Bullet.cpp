#include "Bullet.h"

Bullet::Bullet()
{
}

void Bullet::Initialize()
{
	size_ = { 50.0f, 50.0f };
	isAttack_ = false;
	position_ = { 0.0f, 0.0f };
	direction_ = Direction::kLeft;
	aabb_.max.x = position_.x + size_.x;
	aabb_.max.y = position_.y + size_.y;
	aabb_.min.x = position_.x - size_.x;
	aabb_.min.y = position_.y - size_.y;
}

void Bullet::Update()
{
	velocity_ = {};

	//攻撃中
	if (isAttack_) {
		Shot();
	}

	//進ませる
	position_ = position_ + velocity_;

	//AABBの計算
	aabb_.max.x = position_.x + size_.x;
	aabb_.max.y = position_.y + size_.y;
	aabb_.min.x = position_.x - size_.x;
	aabb_.min.y = position_.y - size_.y;

}

void Bullet::Draw()
{
	if (isAttack_) {
		Novice::DrawEllipse((int)position_.x, (int)position_.y, int(size_.x / 2.0f), int(size_.y / 2.0f), 0.0f, WHITE, kFillModeSolid);
	}
}

void Bullet::Shot()
{
	//左を向いていたら
	if (direction_ == Direction::kLeft) {
		velocity_.x = -6.0f;
	}
	//右を向いていたら
	else if (direction_ == Direction::kRight) {
		velocity_.x = 6.0f;
	}

	//画面外に行ったら消す
	if (position_.x < -50.0f || position_.x > 1350.0f) {
		isAttack_ = false;
		position_.x = 0.0f;
	}

}

void Bullet::SetIsAttack(bool isAttack)
{
	isAttack_ = isAttack;
}

void Bullet::SetPosition(Vector2 position)
{
	position_ = position;
}

void Bullet::SetDirection(Direction direction)
{
	direction_ = direction;
}

AABB Bullet::GetAABB()
{
	return aabb_;
}
