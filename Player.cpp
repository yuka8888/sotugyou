#include "Player.h"
#include "MapChipManager.h"

void Player::Initialize()
{
	paths_ = Direction::kNone;
}

void Player::dicePhaseUpdate()
{
	//すごろく上をを移動
	if (paths_ == Direction::kLeft) {
		translation_.x -= mapChipManager_->GetBlockSize().x;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kRight) {
		translation_.x += mapChipManager_->GetBlockSize().x;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kUp) {
		translation_.y -= mapChipManager_->GetBlockSize().y;
		paths_ = Direction::kNone;
	}
	else if (paths_ == Direction::kDown) {
		translation_.y += mapChipManager_->GetBlockSize().y;
		paths_ = Direction::kNone;
	}
}

void Player::ActionGameUpdate()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	Move();

	aabb_.max = { translation_.x + kWidth_ / 2.0f, translation_.y + kHeight_ / 2.0f };
	aabb_.min = { translation_.x - kWidth_ / 2.0f, translation_.y - kHeight_ / 2.0f };
}

void Player::Draw()
{
	Novice::DrawBox(int(translation_.x - kWidth_ / 2.0f), int(translation_.y - kHeight_ / 2.0f), (int)kWidth_, (int)kHeight_, 0.0f, BLUE, kFillModeSolid);

}

void Player::SetTranslation(Vector2 translation)
{
	translation_ = translation;
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
	mapChipPosition_ = mapChipManager_->GetMapChipIndexSetByPosition(translation_);
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
		isJump = true;
		isGround_ = false;
		acceleration_.y = -10.0f;
	}

	//ジャンプしていたら
	if (!isGround_) {
		acceleration_.y += 0.5f;
	}


	velocity_ = velocity_ + acceleration_;

	translation_ = translation_ + velocity_;

	if (translation_.y > kGround_) {
		isGround_ = true;
		isJump = false;
		acceleration_ = {};
		translation_.y = kGround_;
	}

}
