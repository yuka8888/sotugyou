#include "ShootingItem.h"
#include <Novice.h>

ShootingItem::ShootingItem() : pos_({ 0, 0 }), radius_(16), isAlive_(false) {}

void ShootingItem::Initialize(Vector2 spawnPos)
{
    pos_ = spawnPos;
    radius_ = 16;
    isAlive_ = true;
}

void ShootingItem::Update()
{
    if (isAlive_)
    {
        pos_.x -= 2; // ゆっくり下に落ちる
        if (pos_.x < 0 - radius_) { // 画面外に出たら消える
            isAlive_ = false;
        }
    }
}

void ShootingItem::Draw() const
{
    if (isAlive_)
    {
        Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y), radius_, radius_, 0.0f, GREEN, kFillModeSolid);
    }
}

bool ShootingItem::CheckCollision(Vector2 playerPos, int playerRadius) const
{
    if (!isAlive_)
    {
        return false;
    }
    Vector2 distance = { pos_.x - playerPos.x, pos_.y - playerPos.y };
    float distanceSquared = distance.x * distance.x + distance.y * distance.y;
    float radiusSum = float(radius_ + playerRadius);
    return distanceSquared <= radiusSum * radiusSum;
}
