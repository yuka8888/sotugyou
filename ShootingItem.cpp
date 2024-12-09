#include "ShootingItem.h"
#include <Novice.h>

Item::Item() : pos_({ 0, 0 }), radius_(16), isAlive_(false) {}

void Item::Initialize(Vector2 spawnPos)
{
    pos_ = spawnPos;
    radius_ = 16;
    isAlive_ = true;
}

void Item::Update()
{
    if (isAlive_)
    {
        pos_.x -= 2; // ‚ä‚Á‚­‚è‰º‚É—Ž‚¿‚é
        if (pos_.x < 0 - radius_) { // ‰æ–ÊŠO‚Éo‚½‚çÁ‚¦‚é
            isAlive_ = false;
        }
    }
}

void Item::Draw() const
{
    if (isAlive_)
    {
        Novice::DrawEllipse(static_cast<int>(pos_.x), static_cast<int>(pos_.y), radius_, radius_, 0.0f, GREEN, kFillModeSolid);
    }
}

bool Item::CheckCollision(Vector2 playerPos, int playerRadius) const
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
