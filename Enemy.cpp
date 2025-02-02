#include "Enemy.h"

void Enemy::Initialize()
{
	currentTime_ = (unsigned int)time(nullptr);
	srand(currentTime_);

	position_.x = 1350.0f;
	position_.y = float(rand() % 650 + 35);

	velocity_.x = 5.0f;
	aabb_ = {};

	normalTexture = Novice::LoadTexture("./Resources/enemy_shooting_mini1.png");
	trackingTexture = Novice::LoadTexture("./Resources/enemy_shooting_mini2.png");
	rushTexture = Novice::LoadTexture("./Resources/enemy_shooting_mini3.png");

}

void Enemy::Update()
{
	if (isStart_) {
		Move();
	}
}

void Enemy::Draw()
{
	if (type_ == Type::kNormal && isStart_) {
		for (int i = 0; i < kBulletNum; i++) {
			bullet_[i]->Draw();
		}
	}

	if (isStart_ && !isDeath_) {
		switch (type_)
		{
			case Type::kNormal:
				Novice::DrawSprite(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), normalTexture, 1.0f, 1.0f, 0.0f, WHITE);
				break;
			case Type::kTraching:
				Novice::DrawSprite(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), trackingTexture, 1.0f, 1.0f, 0.0f, WHITE);
				break;
			case Type::kRush:
				Novice::DrawSprite(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), rushTexture, 1.0f, 1.0f, 0.0f, WHITE);
				break;
			default:
				break;
		}
	}
}

void Enemy::SetPlayerPosition(Vector2 playerPosition)
{
	playerPosition_ = playerPosition;
}

Type Enemy::GetType()
{
	return type_;
}

void Enemy::IsStart(bool isStart)
{
	isStart_ = isStart;

	if (isStart_) {
		//攻撃タイプを設定
		int random = rand() % 3;
		if (random == 0) {
			type_ = Type::kNormal;
			for (int i = 0; i < kBulletNum; i++) {
				bullet_[i] = new Bullet;
				bullet_[i]->Initialize();
			}
		}
		else if (random == 1) {
			type_ = Type::kTraching;
		}
		else if (random == 2) {
			type_ = Type::kRush;
		}

		//座標を設定
		position_.x = 1300.0f;
		position_.y = float(rand() % 650 + 35);

	}
}

bool Enemy::IsStart()
{
	return isStart_;
}

void Enemy::IsCollision(bool isCollision)
{
	isCollision_ = isCollision;
}

bool Enemy::IsCollision()
{
	return isCollision_;
}

void Enemy::IsBulletCollision(bool isBulletCollision, int i)
{
	bullet_[i]->IsCollision(isBulletCollision);
}

bool Enemy::IsBulletCollision(int i)
{
	return bullet_[i]->IsCollision();
}

bool Enemy::isBulletAttack(int i)
{
	return bullet_[i]->IsAttack();
}

bool Enemy::IsNothing()
{
	return isNothing;
}

bool Enemy::IsDeath()
{
	return isDeath_;
}

int Enemy::GetBulletNum()
{
	return kBulletNum;
}

AABB Enemy::GetBulletAABB(int i)
{
	return bullet_[i]->GetAABB();
}

void Enemy::IsDeath(bool isDeath)
{
	isDeath_ = isDeath;
}

AABB Enemy::GetAABB()
{
	return aabb_;
}

void Enemy::Move()
{
	velocity_ = {};
	if (position_.x > 1000.0f) {
		velocity_.x = -5.0f;
	}
	else {
		switch (type_)
		{
			case Type::kNormal:
				if (direction_ == Direction::kDown) {
					velocity_.y = 3.0f;
					//方向転換
					if (position_.y > kWindowHeight - size_.y) {
						direction_ = Direction::kUp;
						velocity_.y = -3.0f;
					}
				}
				else if (direction_ == Direction::kUp) {
					velocity_.y = -3.0f;
					//方向転換
					if (position_.y < size_.y) {
						direction_ = Direction::kDown;
						velocity_.y = 3.0f;
					}
				}

				isNothing = true;


				//定期的に球を打つ
				for (int i = 0; i < kBulletNum; i++) {
					attackTimer_ += 0.01f;
					if (attackTimer_ >= 1.0f && !bullet_[i]->IsAttack() && !isDeath_) {
						attackTimer_ = 0.0f;
						bullet_[i]->IsAttack(true);
						bullet_[i]->SetPosition(position_ + Vector2{ 0.0f, size_.y / 2.0f });
						bullet_[i]->SetDirection(Direction::kLeft);
					}
					else if (bullet_[i]->IsAttack()) {
						bullet_[i]->Update();
						isNothing = false;
					}

				}
				break;
			case Type::kTraching:
				velocity_.x = -5.0f;

				//プレイヤーの位置に進む
				if (playerPosition_.y > position_.y) {
					velocity_.y = 2.0f;
				}
				else {
					velocity_.y = -2.0f;
				}
				break;
			case Type::kRush:
				velocity_.x = -5.0f;
				break;
			default:
				break;
		}
	}

	position_ = position_ + velocity_;

	aabb_.max.x = position_.x + size_.x / 2.0f;
	aabb_.max.y = position_.y + size_.y / 2.0f;
	aabb_.min.x = position_.x - size_.x / 2.0f;
	aabb_.min.y = position_.y - size_.y / 2.0f;

	if (position_.x < -size_.x) {
		isStart_ = false;
	}
}
