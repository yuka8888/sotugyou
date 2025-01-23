#pragma once
#include <vector>
#include "ShootingEnemy.h"
#include"ShootingItemManager.h"

class ShootingEnemyManager
{
private:
	std::vector<ShootingEnemy> enemies_; // 複数の敵を管理
	int spawnTimer_;             // 敵生成タイマー
	ShootingItemManager* itemManager_;

public:
	ShootingEnemyManager(ShootingItemManager* itemManager);
	void Initialize();
	void Update();
	void Draw();
	std::vector<ShootingEnemy>& GetEnemies() { return enemies_; } // 非constで返す
	// constバージョンも必要なら
	const std::vector<ShootingEnemy>& GetEnemies() const { return enemies_; }
	//void OnCollision(Enemy& enemy); // 敵の状態を更新する関数
	void OnCollision(int index); // インデックスで敵を指定して更新する関数
};
