#include "ShootingEnemy.h"
#include "ShootingItemManager.h"
#include "Novice.h"

extern ItemManager itemManager; // アイテムマネージャを参照

void Enemy::Initalize()
{
	this->enemyPos_.x = 640.0f;
	this->enemyPos_.y = 20.0f;
	this->enemySpeed_.x = 3.0f;
	this->enemySpeed_.y = 0.0f;
	this->enemyRadius_ = 16.0f;
	this->deathFrame_ = 0;
	this->isEnemyAlive_ = true;
}

void Enemy::OnCollision() { isEnemyAlive_ = false; }

void Enemy::ReturnAlive() { isEnemyAlive_ = true; }

void Enemy::Update()
{
	enemyPos_.x += enemySpeed_.x;
}

void Enemy::Draw() const
{
	if (isEnemyAlive_ == true)
	{
		Novice::DrawEllipse(
			int(enemyPos_.x), int(enemyPos_.y), int(enemyRadius_), int(enemyRadius_), 0.0f, RED,
			kFillModeSolid);
	}
}

void Enemy::SetEnemyPosition(Vector2 position)
{
	enemyPos_ = position;
}

void Enemy::SetSpeed(Vector2 speed)
{
	enemySpeed_.x = speed.x;
	enemySpeed_.y = speed.y;
}
