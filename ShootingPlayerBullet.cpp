#include "ShootingPlayerBullet.h"
#include <Novice.h>

// �R���X�g���N�^
Bullet::Bullet()
{
    for (int i = 0; i < bulletNum; i++)
    {
        bullets_[i].pos = { 0, 0 };
        bullets_[i].isShot = false;
    }
    radius_ = 4;
    speed_ = 8;
}

// �e�̍X�V����
void Bullet::Update()
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (bullets_[i].isShot)
        {
            bullets_[i].pos.x += speed_;
            if (bullets_[i].pos.x > 1280)
            { // ��ʊO�ɏo���烊�Z�b�g
                bullets_[i].isShot = false;
            }
        }
    }
}

// �e�̕`�揈��
void Bullet::Draw()
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (bullets_[i].isShot)
        {
            Novice::DrawEllipse(
                static_cast<int>(bullets_[i].pos.x),
                static_cast<int>(bullets_[i].pos.y),
                radius_,
                radius_,
                0.0f,
                BLUE,
                kFillModeSolid
            );
        }
    }
}

// �e�𔭎�
void Bullet::Fire(Vector2 startPos)
{
    for (int i = 0; i < bulletNum; i++)
    {
        if (!bullets_[i].isShot) {
            bullets_[i].pos = startPos; // ���ˈʒu��ݒ�
            bullets_[i].isShot = true; // ���ˏ�Ԃɐݒ�
            break;
        }
    }
}

// �e�̃��Z�b�g
void Bullet::ResetBullet(int index)
{
    if (index >= 0 && index < bulletNum)
    {
        bullets_[index].isShot = false; // ���ˏ�Ԃ�����
    }
}

// �e�̈ʒu���擾
Vector2 Bullet::GetBulletPos(int index) const
{
    if (index >= 0 && index < bulletNum)
    {
        return bullets_[index].pos;
    }
    return { 0, 0 };
}

// �e�̔��ˏ�Ԃ��擾
bool Bullet::GetBulletIsShot(int index) const
{
    if (index >= 0 && index < bulletNum)
    {
        return bullets_[index].isShot;
    }
    return false;
}
