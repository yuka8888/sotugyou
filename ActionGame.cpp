#include "ActionGame.h"

ActionGame::ActionGame()
{
}

ActionGame::~ActionGame()
{
	delete bullet_;
}

void ActionGame::Initialize()
{
	attackTimer_ = 0.0f;
	bullet_ = new Bullet;
	bullet_->Initialize();
	bullet_->SlimeInitialize();
	isInvincibleTime_ = false;
	invincibleTimer_ = 0.0f;
	currentTime_ = (unsigned int)time(nullptr);
	srand(currentTime_);
	position_.y = kGroundPosition - kHeight_ / 2.0f;
	position_.x = 400.0f;
	aabb.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };
	direction_ = Direction::kRight;
	isClear_ = false;
	backGroundTexture_ = Novice::LoadTexture("./Resources/actionbg.png");
}

void ActionGame::Update()
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

	if (hp_ <= 0) {
		isClear_ = true;
	}
	AnimationTimer();
}

void ActionGame::Draw()
{
	Novice::DrawSprite(0, 0, backGroundTexture_, 1.0f, 1.0f, 0.0f, WHITE);

	if (direction_ == kRight) {
		Novice::DrawSpriteRect(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), int(kWidth_ * int(textureTimer_ / 30)), 0,
			int(kWidth_), int(kHeight_), slimeRightTexture_, (kWidth_ / (kWidth_ * 4)), 1.0f, 0.0f, WHITE);
	}
	else if (direction_ == kLeft) {
		Novice::DrawSpriteRect(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), int(kWidth_ * int(textureTimer_ / 30)), 0,
			int(kWidth_), int(kHeight_), slimeLeftTexture_, (kWidth_ / (kWidth_ * 4)), 1.0f, 0.0f, WHITE);
	}
	bullet_->Draw();
}

AABB ActionGame::GetAABB()
{
	return aabb;
}

AABB ActionGame::GetBulletAABB()
{
	return bullet_->GetAABB();
}

void ActionGame::SetHp(int hp)
{
	hp_ = hp;
}

int ActionGame::GetHp()
{
	return hp_;
}

void ActionGame::IsCollision(bool isCollision)
{
	isCollision_ = isCollision;
}

bool ActionGame::IsPreCollision()
{
	return isPreCollision_;
}

void ActionGame::SwitchState()
{
	invincibleTimer_ += 0.01f;

	//タイマーで無敵時間とそうじゃない時の切り替え
	if (invincibleTimer_ >= 3.0f && isInvincibleTime_ == false) {
		isInvincibleTime_ = true;
		invincibleTimer_ = 0.0f;
	}
	else if (invincibleTimer_ >= 3.0f && isInvincibleTime_) {
		isInvincibleTime_ = true;
		invincibleTimer_ = 0.0f;
	}
}

void ActionGame::Attack()
{
	//攻撃間隔
	attackTimer_ += 0.01f;

	//攻撃するタイミングになったら
	if (attackTimer_ >= 1.0f) {
		bullet_->IsAttack(true);
		bullet_->SetPosition(position_);
		bullet_->SetDirection(direction_);
		attackTimer_ = 0.0f;
	}
}

void ActionGame::SetPlayerPosition(Vector2 playerPosition)
{
	playerPosition_ = playerPosition;
}

bool ActionGame::IsClear()
{
	return isClear_;
}

void ActionGame::AnimationTimer()
{
	//アニメーションタイマー
	textureTimer_++;
	if (textureTimer_ >= 120) {
		textureTimer_ = 0;
	}
}

void ActionGame::Move()
{
	moveTimer_ += 0.01f;

	//左右の移動を一定時間でプレイヤーのいる方向に変える
	if (position_.x < playerPosition_.x && moveTimer_ >= 1.0f) {
		velocity_.x = 3.0f;
		direction_ = Direction::kRight;
		moveTimer_ = 0.0f;
	}
	else if (position_.x > playerPosition_.x && moveTimer_ >= 1.0f) {
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

