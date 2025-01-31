#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
	delete bullet_;
}

void Boss::Initialize()
{
	attackTimer_ = 0.0f;
	bullet_ = new Bullet;
	bullet_->Initialize();
	isInvincibleTime_ = false;
	invincibleTimer_ = 0.0f;
	currentTime_ = (unsigned int)time(nullptr);
	srand(currentTime_);
	position_.y = kGroundPosition - kHeight_ / 2.0f;
	position_.x = 400.0f;
	aabb.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };
	direction_ = Direction::kRight;
}

void Boss::Update()
{
	isPreCollision_ = isCollision_;
	isCollision_ = false;

	//攻撃
	Attack();

	bullet_->Update();
	//AABBの計算
	aabb.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };

	//移動
	Move();
}

void Boss::Draw()
{
	//無敵かによって見た目変える
	if (isInvincibleTime_) {
		Novice::DrawBox(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, RED, kFillModeSolid);
	}
	else {
		Novice::DrawBox(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, BLACK, kFillModeSolid);
	}

	bullet_->Draw();


}

AABB Boss::GetAABB()
{
	return aabb;
}

AABB Boss::GetBulletAABB()
{
	return bullet_->GetAABB();
}

void Boss::SetHp(int hp)
{
	hp_ = hp;
}

int Boss::GetHp()
{
	return hp_;
}

void Boss::IsCollision(bool isCollision)
{
	isCollision_ = isCollision;
}

bool Boss::IsPreCollision()
{
	return isPreCollision_;
}

void Boss::SwitchState()
{
	invincibleTimer_ += 0.01f;

	//タイマーで無敵時間とそうじゃない時の切り替え
	if (invincibleTimer_ >= 5.0f && isInvincibleTime_ == false) {
		isInvincibleTime_ = true;
		invincibleTimer_ = 0.0f;
	}
	else if (invincibleTimer_ >= 5.0f && isInvincibleTime_) {
		isInvincibleTime_ = true;
		invincibleTimer_ = 0.0f;
	}
}

void Boss::Attack()
{
	//攻撃間隔
	attackTimer_ += 0.01f;

	//攻撃するタイミングになったら
	if (attackTimer_ >= 2.0f) {
		bullet_->SetIsAttack(true);
		bullet_->SetPosition(position_);
		bullet_->SetDirection(direction_);
		attackTimer_ = 0.0f;
	}
}

void Boss::SetPlayerPosition(Vector2 playerPosition)
{
	playerPosition_ = playerPosition;
}

void Boss::Move()
{
	moveTimer_ += 0.01f;

	//左右の移動を一定時間でプレイヤーのいる方向に変える
	if (position_.x < playerPosition_.x && moveTimer_ >= 3.0f) {
		velocity_.x = 3.0f;
		direction_ = Direction::kRight;
		moveTimer_ = 0.0f;
	}
	else if (position_.x > playerPosition_.x && moveTimer_ >= 3.0f) {
		velocity_.x = -3.0f;
		direction_ = Direction::kLeft;
		moveTimer_ = 0.0f;
	}

	position_ = position_ + velocity_;

	if (position_.x >= kWindowWidth) {
		position_.x = kWindowWidth;
	}
	else if (position_.x <= 0) {
		position_.x = 0;
	}

}

