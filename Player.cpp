#include "Player.h"
#include "MapChipManager.h"

Player::~Player()
{
	delete bullet_;
}

void Player::Initialize()
{
	paths_ = Direction::kNone;
	bullet_ = new Bullet;
	bullet_->Initialize();
}

void Player::dicePhaseUpdate()
{
	//すごろく上をを移動
	if (paths_ == Direction::kLeft) {
		position_.x -= mapChipManager_->GetBlockSize().x;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kRight) {
		position_.x += mapChipManager_->GetBlockSize().x;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kUp) {
		position_.y -= mapChipManager_->GetBlockSize().y;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kDown) {
		position_.y += mapChipManager_->GetBlockSize().y;
		paths_ = Direction::kNone;
	}
}

void Player::ActionGameUpdate()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	isPreCollision_ = isCollision_;
	isCollision_ = false;

	Move();

	Attack();

	bullet_->Update();

	aabb_.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb_.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };
}

void Player::BossUpdate()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	Move();

	aabb_.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb_.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };

}

void Player::Draw()
{
	Novice::DrawBox(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, BLUE, kFillModeSolid);

	bullet_->Draw();

	ImGui::Begin("Player");
	ImGui::DragInt("Attack", &attack_, 1);
	ImGui::DragInt("hp", &hp_, 1);
	ImGui::DragFloat2("position", &position_.x, 0.1f);
	ImGui::End();
}

void Player::SetPosition(Vector2 translation)
{
	position_ = translation;
}

void Player::SetPaths(Direction paths)
{
	paths_ = paths;
}

void Player::SetMapChipPosition(IndexSet index)
{
	mapChipPosition_ = index;
}

IndexSet Player::GetMapChipPosition()
{
	mapChipPosition_ = mapChipManager_->GetMapChipIndexSetByPosition(position_);
	return mapChipPosition_;
}

void Player::SetMapChipManager(MapChipManager* mapChipManager)
{
	mapChipManager_ = mapChipManager;
}

AABB Player::GetAABB()
{
	return aabb_;
}

void Player::SetAttack(int attack)
{
	attack_ = attack;
}

void Player::SetHp(int hp)
{
	hp_ = hp;
}

int Player::GetAttack()
{
	return attack_;
}

int Player::GetHp()
{
	return hp_;
}

int Player::GetMaxHp()
{
	return maxHp_;
}

void Player::SetMaxHp(int maxHp)
{
	maxHp_ = maxHp;
}

AABB Player::GetBulletAABB()
{
	return bullet_->GetAABB();
}

Vector2 Player::GetPosition()
{
	return position_;
}

void Player::IsCollision(bool isCollision)
{
	isCollision_ = isCollision;
}

bool Player::IsPreCollision()
{
	return isPreCollision_;
}


void Player::Move()
{
	velocity_ = {};

	//移動
	if (Novice::CheckHitKey(DIK_A) || Novice::CheckHitKey(DIK_LEFTARROW)) {
		direction_ = Direction::kLeft;
		velocity_.x = -5.0f;
	}
	else if (Novice::CheckHitKey(DIK_D) || Novice::CheckHitKey(DIK_RIGHTARROW)) {
		direction_ = Direction::kRight;
		velocity_.x = 5.0f;
	}

	//スペースキーでジャンプ
	if (isGround_ && (keys[DIK_W] || keys[DIK_UPARROW])) {
		isJump_ = true;
		isGround_ = false;
		acceleration_.y = -10.0f;
	}

	//ジャンプしていたら
	if (!isGround_) {
		acceleration_.y += 0.5f;
	}


	velocity_ = velocity_ + acceleration_;

	position_ = position_ + velocity_;

	if (position_.y >= kGroundPosition - kHeight_ / 2.0f) {
		isGround_ = true;
		isJump_ = false;
		acceleration_ = {};
		position_.y = kGroundPosition - kHeight_ / 2.0f;
	}
	else {
		isGround_ = false;
		isJump_ = true;
	}

}

void Player::Attack()
{
	//スペースキーで攻撃
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !isAttack_) {
		isAttack_ = true;
		bullet_->SetIsAttack(true);
		bullet_->SetPosition(position_);
		bullet_->SetDirection(direction_);
	}

	//攻撃中
	if (isAttack_) {
		attackTimer_ += 0.01f;
		//クールタイム
		if (attackTimer_ >= 0.5f) {
			isAttack_ = false;
			attackTimer_ = 0.0f;
		}
	}
}
