#pragma once
#include "Vector2.h"

struct BulletData
{
    Vector2 pos;
    bool isShot;
};

class ShootingBullet
{
public:
    static const int bulletNum = 10;

private:
    BulletData bullets_[bulletNum];
    int speed_;
    int radius_; // 半径

public:
    ShootingBullet();
    void Update();
    void Draw();
    void Fire(Vector2 startPos);
    void ResetBullet(int index);
    Vector2 GetBulletPos(int index) const;
    bool GetBulletIsShot(int index) const;

    // 半径を取得する関数を追加
    int GetRadius() const { return radius_; }
};
