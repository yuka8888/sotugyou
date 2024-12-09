#include "ShootingPlayer.h"
#include<Novice.h>
#include"ShootingPlayer.h"
#include <cassert>

ItemManager::ItemManager() : player_(nullptr) {}

void ItemManager::Initialize()
{
	items_.clear();
}

void ItemManager::Update(Vector2 playerPos, int playerRadius)
{
	for (auto& item : items_)
	{
		item.Update();
		if (item.CheckCollision(playerPos, playerRadius))
		{
			// �v���C���[�ƏՓ˂�����A�C�e�����ʂ𔭓�
			 // �A�C�e�����擾���ꂽ�ꍇ
			Novice::ScreenPrintf(0, 20, "Item collected!");
			item.SetAlive(false); // �A�C�e��������

			player_->SetBulletType(PlayerBulletType::SpreadShot);
		}
	}
}

void ItemManager::Draw()
{
	for (const auto& item : items_)
	{
		item.Draw();
	}
}

void ItemManager::SpawnItem(Vector2 spawnPos)
{
	Item newItem;
	newItem.Initialize(spawnPos);
	items_.push_back(newItem);
}

bool ItemManager::CheckCollision(Vector2 playerPos, int playerRadius) {
	// �S�ẴA�C�e���ɑ΂��ďՓ˔�����`�F�b�N
	for (auto& item : items_) {
		if (item.GetAlive()) { // �������Ă���A�C�e���̂ݔ���
			Vector2 distance = {
				playerPos.x - item.GetPos().x,
				playerPos.y - item.GetPos().y
			};
			float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);
			float radiusSum = float(playerRadius) + item.GetRadius();

			// �v���C���[�ƃA�C�e�����Փ˂��Ă�����
			if (distanceSquared <= radiusSum * radiusSum) {
				item.SetAlive(false); // �A�C�e�����A�N�e�B�u��
				return true; // �Փ˂������������Ƃ�Ԃ�
			}
		}
	}

	return false; // �ǂ̃A�C�e���Ƃ��Փ˂��Ă��Ȃ�
}

void ItemManager::SetPlayer(Player* player)
{
	player_ = player;
	assert(player_ != nullptr && "Player pointer is null!");
}
