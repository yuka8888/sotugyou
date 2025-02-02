#include "Shooting.h"
#include "Player.h"

Shooting::~Shooting()
{
	delete player_;
	for (int i = 0; i < kEnemyNum; i++) {
		delete enemy_[i];
	}
}

void Shooting::Initialize()
{
	player_ = new Player;
	
	for (int i = 0; i < kEnemyNum; i++) {
		enemy_[i] = new Enemy;
		enemy_[i]->Initialize();
	}
}

void Shooting::Update()
{
	for (int i = 0; i < kEnemyNum; i++) {
		//追尾の敵にプレイヤーの座標を設定
		if (enemy_[i]->GetType() == Type::kTraching) {
			enemy_[i]->SetPlayerPosition(player_->GetPosition());
		}
		enemy_[i]->Update();
	}
}

void Shooting::Draw()
{
	for (int i = 0; i < kEnemyNum; i++) {
		enemy_[i]->Draw();
	}
}

void Shooting::SetPlayer(Player* player)
{
	player_ = player;
}
