#pragma once
#include "ShootingItem.h"
#include <vector>

class Player;

class ItemManager
{
private:
    std::vector<Item> items_;
    Player* player_; // Playerクラスへのポインタを保持

public:
    ItemManager();
    void Initialize();
    void Update(Vector2 playerPos, int playerRadius);
    void Draw();
    void SpawnItem(Vector2 spawnPos);
    bool CheckCollision(Vector2 playerPos, int playerRadius);
    void SetPlayer(Player* player);
};
