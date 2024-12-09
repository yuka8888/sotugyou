#pragma once
#include "ShootingPlayerBullet.h"
#include "ShootingItemManager.h"

enum class PlayerBulletType
{
    Normal,
    SpreadShot
};

class Player
{
private:
    Vector2 pos_;
    int radius_;
    int bulletIntervalFrame_;
    int deathFrame_;
    float speed_;
    bool isAlive_;
    Bullet* bullet_;
    PlayerBulletType bulletType_;
    ItemManager* itemManager_; // ƒƒ“ƒo‚Æ‚µ‚Ä `ItemManager` ‚ğ•Û

public:
    Player(ItemManager* itemManager);
    ~Player();
    void OnCollision();
    void Initalize();
    void Update(char* keys);
    void Draw();
    Vector2 GetPos() const { return pos_; }
    float GetRadius() const { return float(radius_); }
    float GetSpeed() const;

    // ’eŠÇ—ŠÖ˜A‚ÌŠÖ”
    Vector2 GetBulletPos(int index) const { return bullet_->GetBulletPos(index); }
    bool GetBulletIsShot(int index) const { return bullet_->GetBulletIsShot(index); }
    float GetBulletRadius() const { return float(bullet_->GetRadius()); }
    void ResetBullet(int index) { bullet_->ResetBullet(index); }
    void SetBulletType(PlayerBulletType type) { bulletType_ = type; }
    PlayerBulletType GetBulletType() const { return bulletType_; }
    void FireBullets(); // ’e”­Ë‚Ìˆ—‚ğ•ª—£
};
