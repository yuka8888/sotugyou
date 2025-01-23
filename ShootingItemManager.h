#pragma once
#include "ShootingItem.h"
#include <vector>

class ShootingPlayer;

class ShootingItemManager
{
private:
    std::vector<ShootingItem> items_;
    ShootingPlayer* player_; // Playerクラスへのポインタを保持

public:
    ShootingItemManager();
    void Initialize();
    void Update(Vector2 playerPos, int playerRadius);
    void Draw();
    void SpawnItem(Vector2 spawnPos);
    bool CheckCollision(Vector2 playerPos, int playerRadius);
    void SetPlayer(ShootingPlayer* player);
};
