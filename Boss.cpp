#include "Boss.h"

Boss::~Boss()
{
}

void Boss::Initialize()
{
	bossTexture_ = Novice::LoadTexture("./Resources/enemy_shooting.png");

	for (int i = 0; i < kBulletNum_; i++) {
		bullet_[i] = new Bullet;
		bullet_[i]->BossInitialize();
	}

	aabb_ = MakeAABB(position_, size_);
}

void Boss::Update()
{
	velocity_ = {};

	for (int i = 0; i < kBulletNum_; i++) {
		bullet_[i]->BossUpdate();
	}

	if (position_.x >= 1100.0f) {
		velocity_.x = -3.0f;
	}

	theta_ += 4.0f / 60.0f;
	velocity_.y = sinf(theta_);

	Shot();

	position_ = position_ + velocity_;

	if (hp_ <= 0) {
		isAlive_ = false;
	}

	aabb_ = MakeAABB(position_, size_);
}

void Boss::Draw()
{
	for (int i = 0; i < kBulletNum_; i++) {
		bullet_[i]->Draw();
	}
	if (isAlive_) {
		Novice::DrawSprite(int(position_.x - size_.x / 2.0f), int(position_.y - size_.y / 2.0f), bossTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	}

	ImGui::InputInt("bossHp", &hp_, 1);
}

void Boss::SetHp(int hp)
{
	hp_ = hp;
}

int Boss::GetHp()
{
	return hp_;
}

AABB Boss::GetAABB()
{
	return aabb_;
}

int Boss::GetBulletNum()
{
	return kBulletNum_;
}

AABB Boss::GetBulletAABB(int i)
{
	return bullet_[i]->GetAABB();
}

bool Boss::IsBulletCollision(int i)
{
	return bullet_[i]->IsCollision();
}

void Boss::IsBulletCollision(bool isBulletCollision, int i)
{
	bullet_[i]->IsCollision(isBulletCollision);
}

bool Boss::IsBulletAttack(int i)
{
	return bullet_[i]->IsAttack();
}

bool Boss::IsAlive()
{
	return isAlive_;
}

void Boss::Shot()
{
	attackTimer_ += 0.01f;

	//一定間隔で弾発射
	if (attackTimer_ >= 1.0f) {
		for (int i = 0; i < kBulletNum_; i++) {
			if (!bullet_[i]->IsAttack()) {
				attackTimer_ = 0.0f;
				bullet_[i]->IsAttack(true);
				bullet_[i]->SetPosition(position_);
				bullet_[i]->SetDirection(Direction::kLeft);
				break;
			}
		}
	}
}

