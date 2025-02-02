#include "Enemy.h"

void Enemy::Initialize()
{
	currentTime_ = (unsigned int)time(nullptr);
	srand(currentTime_);

	position_.x = 1350.0f;
	position_.y = float(rand() % 650 + 35);

	velocity_.x = 5.0f;

	//攻撃タイプを設定
	int random = rand() % 3;
	if (random == 0) {
		type_ = Type::kNormal;
	}
	else if (random == 1) {
		type_ = Type::kTraching;
	}
	else if (random == 2) {
		type_ = Type::kRush;
	}
}

void Enemy::Update()
{
	Move();
}

void Enemy::Draw()
{
	switch (type_)
	{
		case Type::kNormal:
			Novice::DrawBox(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), (int)size_.x, (int)size_.y, 0.0f, BLUE, kFillModeSolid);
			break;
		case Type::kTraching:
			Novice::DrawBox(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), (int)size_.x, (int)size_.y, 0.0f, RED, kFillModeSolid);
			break;
		case Type::kRush:
			Novice::DrawBox(int(position_.x - size_.x / 2.0f), int(position_.y - size_.x / 2.0f), (int)size_.x, (int)size_.y, 0.0f, BLACK, kFillModeSolid);
			break;
		default:
			break;
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
					if (position_.y > position_.y - size_.y) {
						direction_ = Direction::kUp;
						velocity_.y = -3.0f;
					}
				}
				else if (direction_ == Direction::kUp) {
					velocity_.y = -3.0f;
					//方向転換
					if (position_.y > position_.y - size_.y) {
						direction_ = Direction::kDown;
						velocity_.y = 3.0f;
					}
				}
				break;
			case Type::kTraching:
				velocity_.x = -5.0f;

				//プレイヤーの位置に進む
				if (playerPosition_.y > position_.x) {
					velocity_.y = 1.0f;
				}
				else {
					velocity_.y = -1.0f;
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
}
