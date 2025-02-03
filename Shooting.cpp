#include "Shooting.h"
#include "Player.h"

Shooting::~Shooting()
{
	delete player_;
	delete boss_;
	for (int i = 0; i < kEnemyNum; i++) {
		delete enemy_[i];
	}

}

void Shooting::Initialize()
{
	player_ = new Player;
	player_->Initialize();

	boss_ = new Boss;
	boss_->Initialize();

	for (int i = 0; i < kEnemyNum; i++) {
		enemy_[i] = new Enemy;
		enemy_[i]->Initialize();
	}
	backGroundTexture_ = Novice::LoadTexture("./Resources/shooting_bg.png");

}

void Shooting::Update()
{
	bgPosition.x -= 1.0f;
	bgPosition2.x -= 1.0f;

	if (bgPosition.x <= -1280.0f) {
		bgPosition.x = 1280;
	}
	if (bgPosition2.x <= -1280.0f) {
		bgPosition2.x = 1280;
	}
	spawnTimer += 0.01f;

	player_->BossUpdate();

	boss_->Update();

	Collision();

	for (int i = 0; i < kEnemyNum; i++) {
		//敵をスポーン
		if (!enemy_[i]->IsStart() && spawnTimer >= 1.0f) {
			enemy_[i]->IsStart(true);
			spawnTimer = 0.0f;
			break;
		}
	}

	for (int i = 0; i < kEnemyNum; i++) {
		//追尾の敵にプレイヤーの座標を設定
		if (enemy_[i]->GetType() == Type::kTraching) {
			enemy_[i]->SetPlayerPosition(player_->GetPosition());
		}
		enemy_[i]->Update();

		//弾がすべて消えれば消す
		if (enemy_[i]->IsDeath() && enemy_[i]->IsNothing()) {
			delete enemy_[i];
			enemy_[i] = new Enemy;
			enemy_[i]->Initialize();

		}
	}

	if (!boss_->IsAlive()) {
		isClear_ = true;
	}
	else if (player_->GetHp() <= 0) {
		isGameOver_ = true;
	}
}

void Shooting::Draw()
{
	Novice::DrawSprite((int)bgPosition.x, (int)bgPosition.y, backGroundTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	Novice::DrawSprite((int)bgPosition2.x, (int)bgPosition2.y, backGroundTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	
	player_->BossDraw();

	for (int i = 0; i < kEnemyNum; i++) {
		enemy_[i]->Draw();
	}

	boss_->Draw();
}

void Shooting::SetPlayer(Player* player)
{
	player_ = player;
}

bool Shooting::IsClear()
{
	return isClear_;
}

bool Shooting::IsGameOver()
{
	return isGameOver_;
}

void Shooting::Collision()
{
	//敵とプレイヤーの弾
	for (int i = 0; i < kEnemyNum; i++) {
		for (int j = 0; j < player_->GetBulletNum(); j++) {
			if (player_->IsBulletDraw(j) && enemy_[i]->IsStart()) {
				if (isCollision(enemy_[i]->GetAABB(), player_->GetBulletAABB(j))) {
					enemy_[i]->IsDeath(true);
				}
			}
		}
	}

	//敵とプレイヤー
	for (int i = 0; i < kEnemyNum; i++) {
		if (enemy_[i]->IsStart()) {
			if (isCollision(enemy_[i]->GetAABB(), player_->GetAABB()) && !enemy_[i]->IsCollision()) {
				player_->SetHp(player_->GetHp() - 1);
				enemy_[i]->IsCollision(true);
			}
		}
	}

	//敵の弾とプレイヤー
	for (int i = 0; i < kEnemyNum; i++) {
		if (enemy_[i]->GetType() == Type::kNormal && enemy_[i]->IsStart()) {
			for (int j = 0; j < enemy_[i]->GetBulletNum(); j++) {
				if (enemy_[i]->isBulletAttack(j)) {
					if (isCollision(enemy_[i]->GetBulletAABB(j), player_->GetAABB()) && !enemy_[i]->IsBulletCollision(j)) {
						player_->SetHp(player_->GetHp() - 1);
						enemy_[i]->IsBulletCollision(true, j);
					}
				}
			}
		}
	}

	//ボスの弾とプレイヤー
	for (int i = 0; i < boss_->GetBulletNum(); i++) {
		if (boss_->IsBulletAttack(i)) {
			if (isCollision(boss_->GetBulletAABB(i), player_->GetAABB()) && !boss_->IsBulletCollision(i)) {
				player_->SetHp(player_->GetHp() - 1);
				boss_->IsBulletCollision(true, i);
			}
		}
	}

	//ボスとプレイヤーの弾
	for (int i = 0; i < player_->GetBulletNum(); i++) {
		if (player_->IsBulletDraw(i)) {
			if (isCollision(boss_->GetAABB(), player_->GetBulletAABB(i)) && !player_->IsBulletCollision(i)) {
				boss_->SetHp(boss_->GetHp() - 1);
				player_->IsBulletCollision(true, i);
			}
		}
	}
}
