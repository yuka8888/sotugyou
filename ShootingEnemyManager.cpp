#include "ShootingEnemyManager.h"
#include <cstdlib>
#include <ctime>
#include <cassert>

// コンストラクタでItemManagerへのポインタを受け取る
ShootingEnemyManager::ShootingEnemyManager(ShootingItemManager* itemManager) : spawnTimer_(0), itemManager_(itemManager)
{
	assert(itemManager_ != nullptr && "itemManager is null!");
}


void ShootingEnemyManager::Initialize()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	enemies_.clear();
	spawnTimer_ = 0;
}

void ShootingEnemyManager::Update()
{
	spawnTimer_++;

	if (spawnTimer_ >= 60)
	{ // 敵を生成
		ShootingEnemy newEnemy;
		newEnemy.Initalize();
		float randomY = static_cast<float>(std::rand() % 700 + 20);
		newEnemy.SetEnemyPosition({ 1280.0f, randomY });
		newEnemy.SetSpeed({ -3.0f, 0.0f });
		enemies_.push_back(newEnemy);
		spawnTimer_ = 0;
	}

	for (auto& enemy : enemies_)
	{
		enemy.Update();
	}

	// 敵リストから無効な敵を削除
	enemies_.erase(
		std::remove_if(enemies_.begin(), enemies_.end(), [this](ShootingEnemy& enemy) {
			if (!enemy.GetAlive()) {
				// 敵が死んだらアイテムをスポーン
				itemManager_->SpawnItem(enemy.GetPos());
			}
			return !enemy.GetAlive() || enemy.GetPos().x < -20;
			}),
		enemies_.end());
}

void ShootingEnemyManager::Draw()
{
	for (const auto& enemy : enemies_)
	{
		enemy.Draw();
	}
}

void ShootingEnemyManager::OnCollision(int index)
{
	if (index >= 0 && index < enemies_.size())
	{
		enemies_[index].OnCollision(); // 該当インデックスの敵を更新
	}
}
