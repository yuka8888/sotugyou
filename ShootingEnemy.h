#pragma once
#include "Vector2.h"

class ShootingEnemy
{
private:
    Vector2 enemyPos_;   // 位置
    Vector2 enemySpeed_; // スピード
    int deathFrame_;     // 死んだときのアニメーション
    float enemyRadius_;  // 半径
    bool isEnemyAlive_;  // 生存フラグ

public:
    void Initalize();   // 初期化
    void OnCollision(); // 当たり判定
    void ReturnAlive();
    void Update();      // 更新処理
    void Draw() const;  // 描画処理
    void SetEnemyPosition(Vector2 position);
    float GetRadius() const { return enemyRadius_; }
    bool GetAlive() const { return isEnemyAlive_; }
    Vector2 GetPos() const { return enemyPos_; }
    void SetSpeed(Vector2 speed);
};
