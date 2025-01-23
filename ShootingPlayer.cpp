#include "ShootingPlayer.h"
#include <Novice.h>

void ShootingPlayer::Initalize()
{
    pos_ = { 0, 500 };
    radius_ = 20;
    speed_ = 4.0f;
    bulletIntervalFrame_ = 20;
    isAlive_ = true;
    deathFrame_ = 120;
    bulletType_ = PlayerBulletType::Normal;
    bullet_ = new ShootingBullet();
}

// プレイヤーが初期化する情報
ShootingPlayer::~ShootingPlayer() { delete bullet_; }

ShootingPlayer::ShootingPlayer(ShootingItemManager* itemManager) : itemManager_(itemManager)
{
    // 初期化処理
    bullet_ = new ShootingBullet();
    pos_ = { 0, 500 };
    radius_ = 20;
    speed_ = 4.0f;
    bulletIntervalFrame_ = 20;
    isAlive_ = true;
    deathFrame_ = 120;
    bulletType_ = PlayerBulletType::Normal;
}

void ShootingPlayer::OnCollision()
{
    isAlive_ = false;
    if (isAlive_ == false)
    {
        deathFrame_++;
    }
    if (deathFrame_ == 120)
    {
        isAlive_ = true;
        deathFrame_ = 0;
    }
}

void ShootingPlayer::Update(char* keys)
{
    // 移動処理
    if (keys[DIK_W] || keys[DIK_UP])
    {
        pos_.y -= speed_;
    }
    if (keys[DIK_S] || keys[DIK_DOWN])
    {
        pos_.y += speed_;
    }
    if ((keys[DIK_A] || keys[DIK_LEFT]) && pos_.x >= 0)
    {
        pos_.x -= speed_;
    }
    if ((keys[DIK_D] || keys[DIK_RIGHT]) && pos_.x <= 200)
    {
        pos_.x += speed_;
    }

    // 弾の発射
    if (keys[DIK_SPACE] && bulletIntervalFrame_ == 0)
    {
        FireBullets(); // `FireBullets` を呼び出す
        bulletIntervalFrame_ = 20; // クールタイム
    }

    // アイテムの取得をチェック
    itemManager_->Update(pos_, radius_);

    // 移動範囲の制限
    if (pos_.x > 1260)
    {
        pos_.x = 1260;
    }
    if (pos_.x < 20)
    {
        pos_.x = 20;
    }
    if (pos_.y > 700)
    {
        pos_.y = 700;
    }
    if (pos_.y < 20)
    {
        pos_.y = 20;
    }

    // 弾の更新
    bullet_->Update();

    // クールタイムのカウント
    if (bulletIntervalFrame_ != 0)
    {
        bulletIntervalFrame_--;
    }
}


void ShootingPlayer::Draw()
{
    if (isAlive_ == true)
    {
        Novice::DrawEllipse(
            int(pos_.x), int(pos_.y), int(radius_), int(radius_), 0.0f, WHITE, kFillModeSolid);
        bullet_->Draw();
    }
}

float ShootingPlayer::GetSpeed() const { return speed_; }

void ShootingPlayer::FireBullets()
{
    switch (bulletType_)
    {
        case PlayerBulletType::Normal:
            bullet_->Fire(pos_); // 通常弾
            break;

        case PlayerBulletType::SpreadShot:
            bullet_->Fire(pos_);                  // 真っ直ぐ
            bullet_->Fire({ pos_.x, pos_.y - 20 }); // 45度方向
            bullet_->Fire({ pos_.x, pos_.y + 20 }); // -45度方向
            break;
    }
}
