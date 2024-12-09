#pragma once
#include "Vector2.h"

struct BulletData
{
    Vector2 pos;
    bool isShot;
};

class Bullet
{
public:
    static const int bulletNum = 10;

private:
    BulletData bullets_[bulletNum];
    int speed_;
    int radius_; // ”¼Œa

public:
    Bullet();
    void Update();
    void Draw();
    void Fire(Vector2 startPos);
    void ResetBullet(int index);
    Vector2 GetBulletPos(int index) const;
    bool GetBulletIsShot(int index) const;

    // ”¼Œa‚ğæ“¾‚·‚éŠÖ”‚ğ’Ç‰Á
    int GetRadius() const { return radius_; }
};
