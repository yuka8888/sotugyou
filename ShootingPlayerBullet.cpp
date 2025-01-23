#include "ShootingPlayerBullet.h"
#include <Novice.h>

// コンストラクタ
ShootingBullet::ShootingBullet()
{
    for (int i = 0; i < bulletNum; i++)
    {
        bullets_[i].pos = { 0, 0 };
        bullets_[i].isShot = false;
    }
    radius_ = 4;
    speed_ = 8;
}

// 弾の更新処理
void ShootingBullet::Update()
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (bullets_[i].isShot)
        {
            bullets_[i].pos.x += speed_;
            if (bullets_[i].pos.x > 1280)
            { // 画面外に出たらリセット
                bullets_[i].isShot = false;
            }
        }
    }
}

// 弾の描画処理
void ShootingBullet::Draw()
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (bullets_[i].isShot)
        {
            Novice::DrawEllipse(
                static_cast<int>(bullets_[i].pos.x),
                static_cast<int>(bullets_[i].pos.y),
                radius_,
                radius_,
                0.0f,
                BLUE,
                kFillModeSolid
            );
        }
    }
}

// 弾を発射
void ShootingBullet::Fire(Vector2 startPos)
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (!bullets_[i].isShot) {
            bullets_[i].pos = startPos; // 発射位置を設定
            bullets_[i].isShot = true; // 発射状態に設定
            break;
        }
    }
}

// 弾のリセット
void ShootingBullet::ResetBullet(int index)
{
    if (index >= 0 && index < bulletNum)
    {
        bullets_[index].isShot = false; // 発射状態を解除
    }
}

// 弾の位置を取得
Vector2 ShootingBullet::GetBulletPos(int index) const
{
    if (index >= 0 && index < bulletNum)
    {
        return bullets_[index].pos;
    }
    return { 0, 0 };
}

// 弾の発射状態を取得
bool ShootingBullet::GetBulletIsShot(int index) const
{
    if (index >= 0 && index < bulletNum)
    {
        return bullets_[index].isShot;
    }
    return false;
}
