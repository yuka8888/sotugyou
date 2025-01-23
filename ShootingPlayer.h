#pragma once
#include "ShootingPlayerBullet.h"
#include "ShootingItemManager.h"

enum class PlayerBulletType
{
    Normal,
    SpreadShot
};

class ShootingPlayer
{
private:
    Vector2 pos_;
    int radius_;
    int bulletIntervalFrame_;
    int deathFrame_;
    float speed_;
    bool isAlive_;
    ShootingBullet* bullet_;
    PlayerBulletType bulletType_;
    ShootingItemManager* itemManager_; // メンバとして `ItemManager` を保持

public:
    ShootingPlayer(ShootingItemManager* itemManager);
    ~ShootingPlayer();
    void OnCollision();
    void Initalize();
    void Update(char* keys);
    void Draw();
    Vector2 GetPos() const { return pos_; }
    float GetRadius() const { return float(radius_); }
    float GetSpeed() const;

    // 弾管理関連の関数
    Vector2 GetBulletPos(int index) const { return bullet_->GetBulletPos(index); }
    bool GetBulletIsShot(int index) const { return bullet_->GetBulletIsShot(index); }
    float GetBulletRadius() const { return float(bullet_->GetRadius()); }
    void ResetBullet(int index) { bullet_->ResetBullet(index); }
    void SetBulletType(PlayerBulletType type) { bulletType_ = type; }
    PlayerBulletType GetBulletType() const { return bulletType_; }
    void FireBullets(); // 弾発射の処理を分離
};
