#include "PlayScene.h"
#include "MapChipManager.h"

PlayScene::PlayScene() {
    fade_ = new Fade();
    player_ = new Player();
    ShootingItemManager shootingItemManager;
    shootingPlayer_=new ShootingPlayer(&shootingItemManager);
    itemManager_ = new ShootingItemManager();
    enemyManager_ = new ShootingEnemyManager(itemManager_);
}

PlayScene::~PlayScene() {
    delete fade_;
    delete player_;
    delete itemManager_;
    delete enemyManager_;
}

void PlayScene::Initialize()
{
    fade_->Initialize();
    fade_->Start(Fade::Status::FadeIn, 1.0f);

    player_->Initialize();
    itemManager_->Initialize();
    enemyManager_->Initialize();

    // マップの初期化
    MapChipManager* mapChipManager = new MapChipManager;
    mapChipManager->LoadMapChipCsv("Resources/map.csv");
    kBlockHeight = kWindowHeight / mapChipManager->GetNumBlockVirtical();
    kBlockWidth = kBlockHeight;

    delete mapChipManager;
}

void PlayScene::Update() {
    // キー入力を受け取る
    memcpy(preKeys, keys, 256);
    Novice::GetHitKeyStateAll(keys);

    fade_->Update();
    itemManager_->Update(shootingPlayer_->GetPos(), int(shootingPlayer_->GetRadius()));
    enemyManager_->Update();
    shootingPlayer_->Update(keys);

    // 敵との当たり判定
    for (size_t i = 0; i < enemyManager_->GetEnemies().size(); i++) {
        ShootingEnemy& enemy = enemyManager_->GetEnemies()[i];

        // プレイヤーと敵の当たり判定
        if (Collision(shootingPlayer_->GetPos(), enemy.GetPos(), shootingPlayer_->GetRadius(), enemy.GetRadius())) {
            shootingPlayer_->OnCollision();
            phase_ = Phase::boss; // フェーズ切り替え例
        }

        // 弾と敵の当たり判定
        for (int j = 0; j < ShootingBullet::bulletNum; j++) {
            if (shootingPlayer_->GetBulletIsShot(j) &&
                Collision(shootingPlayer_->GetBulletPos(j), enemy.GetPos(), shootingPlayer_->GetBulletRadius(), enemy.GetRadius())) {
                shootingPlayer_->ResetBullet(j);
                enemy.OnCollision();
            }
        }
    }

    if (Novice::CheckHitKey(DIK_SPACE) && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
        fade_->Start(Fade::Status::FadeOut, 1.0f);
    }

    if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
        phase_ = Phase::dice; // 別フェーズ切り替え例
    }
}

void PlayScene::Draw() 
{
    DrawMap();
    enemyManager_->Draw();
    player_->Draw();
    shootingPlayer_->Draw();
    itemManager_->Draw();
    fade_->Draw();
}

void PlayScene::DrawMap() 
{
    // マップの描画 (元の内容をそのまま使用)
}

bool PlayScene::Collision(Vector2 playerPos, Vector2 enemyPos, float playerRadius, float enemyRadius) {
    Vector2 distance = { playerPos.x - enemyPos.x, playerPos.y - enemyPos.y };
    float disSquared = distance.x * distance.x + distance.y * distance.y;
    float radiusSum = playerRadius + enemyRadius;
    return disSquared <= radiusSum * radiusSum;
}
