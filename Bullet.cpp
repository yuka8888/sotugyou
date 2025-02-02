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
	bulletTexture_= Novice::LoadTexture("./Resources/player_atack1.png");
}

void Bullet::PlayerInitialize()
{
	size_ = { 32.0f, 32.0f };
	isAttack_ = false;
	position_ = { 0.0f, 0.0f };
	direction_ = Direction::kLeft;
	aabb_.max.x = position_.x + size_.x;
	aabb_.max.y = position_.y + size_.y;
	aabb_.min.x = position_.x - size_.x;
	aabb_.min.y = position_.y - size_.y;

	bulletTexture_= Novice::LoadTexture("./Resources/player_atack1.png");
}

void Bullet::BossInitialize()
{
	bulletTexture_ = Novice::LoadTexture("./Resources/player_atack1.png");
	isAttack_ = false;
	position_ = { 0.0f, 0.0f };
	size_ = { 32.0f, 32.0f };
	direction_ = Direction::kLeft;

	aabb_ = MakeAABB(position_, size_);
}

void Bullet::SlimeInitialize()
{
	size_ = { 32.0f, 32.0f };
	isAttack_ = false;
	position_ = { 0.0f, 0.0f };
	direction_ = Direction::kLeft;
	aabb_.max.x = position_.x + size_.x;
	aabb_.max.y = position_.y + size_.y;
	aabb_.min.x = position_.x - size_.x;
	aabb_.min.y = position_.y - size_.y;

	bulletTexture_ = Novice::LoadTexture("./Resources/slime_atack2.png");
}


void Bullet::Update()
{

	//攻撃中
	if (isAttack_) {
		Shot();
	}

	//進ませる
	position_ = position_ + velocity_;

	//画面外に行ったら消す
	if (position_.x < -50.0f || position_.x > 1350.0f) {
		isAttack_ = false;
		position_.x = 0.0f;
		isCollision_ = false;
	}

	aabb_ = MakeAABB(position_, size_);

}

void Bullet::BossUpdate()
{
	velocity_ = {};

	if (isAttack_ == true) {
		theta_ += 4.0f / 60.0f;
		velocity_.y = sinf(theta_) * 2.0f;
		velocity_.x = -5.0f;
	}

	position_ = position_ + velocity_;

	//画面外に行ったら消す
	if (position_.x < -50.0f || position_.x > 1350.0f) {
		isAttack_ = false;
		position_.x = 0.0f;
		isCollision_ = false;
	}

	aabb_ = MakeAABB(position_, size_);

}

void Bullet::Draw()
{
	if (isAttack_) {
		Novice::DrawSprite(int(position_.x - size_.x / 2.0f), int(position_.y - size_.y / 2.0f), bulletTexture_, 1.0f, 1.0f, 0.0f, WHITE);
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
}

void Bullet::IsAttack(bool isAttack)
{
	isAttack_ = isAttack;
}

bool Bullet::IsAttack()
{
	return isAttack_;
}

bool Bullet::IsCollision()
{
	return isCollision_;
}

void Bullet::IsCollision(bool isCollision)
{
	isCollision_ = isCollision;
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
