#pragma once
#include "Vector2.h"

class Enemy
{
private:
    Vector2 enemyPos_;   // �ʒu
    Vector2 enemySpeed_; // �X�s�[�h
    int deathFrame_;     // ���񂾂Ƃ��̃A�j���[�V����
    float enemyRadius_;  // ���a
    bool isEnemyAlive_;  // �����t���O

public:
    void Initalize();   // ������
    void OnCollision(); // �����蔻��
    void ReturnAlive();
    void Update();      // �X�V����
    void Draw() const;  // �`�揈��
    void SetEnemyPosition(Vector2 position);
    float GetRadius() const { return enemyRadius_; }
    bool GetAlive() const { return isEnemyAlive_; }
    Vector2 GetPos() const { return enemyPos_; }
    void SetSpeed(Vector2 speed);
};
