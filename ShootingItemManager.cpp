#include "ShootingItemManager.h"
#include"ShootingPlayer.h"
#include<Novice.h>
#include <cassert>

ShootingItemManager::ShootingItemManager() : player_(nullptr) {}

void ShootingItemManager::Initialize()
{
	items_.clear();
}

void ShootingItemManager::Update(Vector2 playerPos, int playerRadius)
{
	for (auto& item : items_)
	{
		item.Update();
		if (item.CheckCollision(playerPos, playerRadius))
		{
			// プレイヤーと衝突したらアイテム効果を発動
			 // アイテムが取得された場合
			Novice::ScreenPrintf(0, 20, "Item collected!");
			item.SetAlive(false); // アイテムを消す

			player_->SetBulletType(PlayerBulletType::SpreadShot);
		}
	}
}

void ShootingItemManager::Draw()
{
	for (const auto& item : items_)
	{
		item.Draw();
	}
}

void ShootingItemManager::SpawnItem(Vector2 spawnPos)
{
	ShootingItem newItem;
	newItem.Initialize(spawnPos);
	items_.push_back(newItem);
}

bool ShootingItemManager::CheckCollision(Vector2 playerPos, int playerRadius) {
	// 全てのアイテムに対して衝突判定をチェック
	for (auto& item : items_) {
		if (item.GetAlive()) { // 生存しているアイテムのみ判定
			Vector2 distance = {
				playerPos.x - item.GetPos().x,
				playerPos.y - item.GetPos().y
			};
			float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);
			float radiusSum = float(playerRadius) + item.GetRadius();

			// プレイヤーとアイテムが衝突していたら
			if (distanceSquared <= radiusSum * radiusSum) {
				item.SetAlive(false); // アイテムを非アクティブに
				return true; // 衝突が発生したことを返す
			}
		}
	}

	return false; // どのアイテムとも衝突していない
}

void ShootingItemManager::SetPlayer(ShootingPlayer* player)
{
	player_ = player;
	assert(player_ != nullptr && "Player pointer is null!");
}
