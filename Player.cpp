#include "Player.h"
#include "MapChipManager.h"

Player::~Player()
{
	for (int i = 0; i < kBulletNum; i++) {
		delete bullet_[i];
	}
}

void Player::Initialize()
{
	paths_ = Direction::kNone;
	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i] = new Bullet;
		bullet_[i]->PlayerInitialize();
	}
	playerShootingTexture_ = Novice::LoadTexture("./Resources/player_shooting.png");
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

	AnimationTimer();

	aabb_.max = { position_.x + kWidth_ / 2.0f, position_.y + kHeight_ / 2.0f };
	aabb_.min = { position_.x - kWidth_ / 2.0f, position_.y - kHeight_ / 2.0f };
}

void Player::BossUpdate()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	BossMove();

	AnimationTimer();

	if (attackUpNum_ >= 10) {
		coolTime_ = 0.5f;
		isStrongAttack_ = true;
	}
	else if (attackUpNum_ >= 7) {
		coolTime_ = 1.0f;
		isStrongAttack_ = true;
	}
	else if (attackUpNum_ >= 5) {
		coolTime_ = 1.0f;
	}
	else if (attackUpNum_ >= 3) {
		coolTime_ = 1.5f;
	}

	aabb_ = MakeAABB(position_, { kWidth_, kHeight_ });
}

void Player::Draw()
{
	Novice::DrawBox(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, BLUE, kFillModeSolid);

	if (direction_ == kRight) {
		Novice::DrawSpriteRect(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), int(kWidth_ * int(textureTimer_ / 30)), 0,
			int(kWidth_), int(kHeight_), playerRightTexture_, (kWidth_ / (kWidth_ * 2)), 1.0f, 0.0f, WHITE);
	}
	else if (direction_ == kLeft) {
		Novice::DrawSpriteRect(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), int(kWidth_ * int(textureTimer_ / 30)), 0,
			int(kWidth_), int(kHeight_), playerLeftTexture_, (kWidth_ / (kWidth_ * 2)), 1.0f, 0.0f, WHITE);
	}

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i]->Draw();
	}

	ImGui::Begin("Player");
	ImGui::DragInt("Attack", &attack_, 1);
	ImGui::DragInt("hp", &hp_, 1);
	ImGui::DragFloat2("position", &position_.x, 0.1f);
	ImGui::End();
}

void Player::BossDraw()
{
	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i]->Draw();
	}

	Novice::DrawSprite(int(position_.x - kWidth_ / 2.0f), int(position_.y - kHeight_ / 2.0f), playerShootingTexture_, 1.0f, 1.0f, 0.0f, WHITE);

	ImGui::InputInt("PlayerHp", &hp_, 1);
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

AABB Player::GetBulletAABB(int i)
{
	return bullet_[i]->GetAABB();
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

bool Player::IsBulletCollision(int i)
{
	return bullet_[i]->IsCollision();
}

void Player::IsBulletCollision(bool isBulletCollision, int i)
{
	bullet_[i]->IsCollision(isBulletCollision);
}

bool Player::IsBulletDraw(int i)
{
	return bullet_[i]->IsAttack();
}

void Player::IsBulletDraw(bool isBulletDraw, int i)
{
	bullet_[i]->IsAttack(isBulletDraw);
}

int Player::GetBulletNum()
{
	return kBulletNum;
}

int Player::GetAttackUpNum_()
{
	return attackUpNum_;
}

void Player::SetAttackUpNum_(int attackUpNum)
{
	attackUpNum_ = attackUpNum;
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

void Player::BossMove()
{
	velocity_ = {};

	//移動
	if (Novice::CheckHitKey(DIK_A) || Novice::CheckHitKey(DIK_LEFTARROW)) {
		direction_ = Direction::kLeft;
		velocity_.x = -1.0f;
	}
	if (Novice::CheckHitKey(DIK_D) || Novice::CheckHitKey(DIK_RIGHTARROW)) {
		direction_ = Direction::kRight;
		velocity_.x = 1.0f;
	}
	if (Novice::CheckHitKey(DIK_W) || Novice::CheckHitKey(DIK_UPARROW)) {
		direction_ = Direction::kUp;
		velocity_.y = -1.0f;
	}
	if (Novice::CheckHitKey(DIK_S) || Novice::CheckHitKey(DIK_DOWNARROW)) {
		direction_ = Direction::kDown;
		velocity_.y = 1.0f;
	}

	velocity_ = Normalize(velocity_) * Vector2 { speed_, speed_ };

	BossAttack();

	position_ = position_ + velocity_;

	if (position_.x < kWidth_ / 2.0f) {
		position_.x = kWidth_ / 2.0f;
	}
	if (position_.x > 700.0f) {
		position_.x = 700.0f;
	}
	if (position_.y < kHeight_ / 2.0f) {
		position_.y = kHeight_ / 2.0f;
	}
	if (position_.y > 720.0f - kHeight_ / 2.0f) {
		position_.y = 720.0f - kHeight_ / 2.0f;
	}
}

void Player::Attack()
{
	for (int i = 0; i < kBulletNum; i++) {
		//スペースキーで攻撃
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !bullet_[i]->IsAttack()) {
			isAttack_ = true;
			bullet_[i]->IsAttack(true);
			bullet_[i]->SetPosition(position_);
			bullet_[i]->SetDirection(direction_);
			break;
		}

	}

	//攻撃中
	if (isAttack_) {
		attackTimer_ += 0.04f;
		//クールタイム
		if (attackTimer_ >= coolTime_) {
			isAttack_ = false;
			attackTimer_ = 0.0f;
		}
	}

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i]->Update();
	}

}

void Player::BossAttack()
{
	//スペースキーで攻撃
	for (int i = 0; i < kBulletNum; i++) {
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !isAttack_ && !bullet_[i]->IsAttack()) {
			if (isStrongAttack_) {
				isAttack_ = true;
				bullet_[i]->IsAttack(true);
				bullet_[(i + kBulletNum / 2) % kBulletNum]->IsAttack(true);
				bullet_[i]->SetPosition(position_ + Vector2{ 0.0f, -8.0f });
				bullet_[(i + kBulletNum / 2) % kBulletNum]->SetPosition(position_ + Vector2{ 0.0f, 8.0f });
				bullet_[i]->SetDirection(Direction::kRight);
				bullet_[(i + kBulletNum / 2) % kBulletNum]->SetDirection(Direction::kRight);
			}
			else {
				isAttack_ = true;
				bullet_[i]->IsAttack(true);
				bullet_[i]->SetPosition(position_ + Vector2{ 0.0f, 0.0f });
				bullet_[i]->SetDirection(Direction::kRight);
			}
			break;
		}
	}

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i]->Update();
	}

	//攻撃中
	if (isAttack_) {
		attackTimer_ += 0.03f;
		//クールタイム
		if (attackTimer_ >= coolTime_) {
			isAttack_ = false;
			attackTimer_ = 0.0f;
		}
	}


}

void Player::AnimationTimer()
{
	//アニメーションタイマー
	textureTimer_++;
	if (textureTimer_ >= 60) {
		textureTimer_ = 0;
	}
}