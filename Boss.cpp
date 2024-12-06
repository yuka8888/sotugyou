#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Initialize()
{
}

void Boss::Update()
{
	WaveAtk();

	if (Novice::CheckHitKey(DIK_Q)) {
		isAttack = true;
	}

}

void Boss::WaveAtk(){
	if (waveAtk_L[0].isAtk == 1) {	//先頭--左
		waveAtk_L[0].timer++;
		waveAtk_L[0].leftX -= waveAtk_L[0].spd;
		waveAtk_L[0].rightX -= waveAtk_L[0].spd;
	}
	if (waveAtk_L[0].timer >= waveAtk_L[0].maxTime) {
		waveAtk_L[0].scale_h = -waveAtk_L[0].oriScale;
	}
	if (waveAtk_L[0].rightX <= -waveAtk_L[0].size.w) {
		waveAtk_L[0].isAtk = 0;
	}
	if (waveAtk_R[0].isAtk == 1) {	//先頭--右
		waveAtk_R[0].timer++;
		waveAtk_R[0].leftX += waveAtk_R[0].spd;
		waveAtk_R[0].rightX += waveAtk_R[0].spd;
	}
	if (waveAtk_R[0].timer >= waveAtk_R[0].maxTime) {
		waveAtk_R[0].scale_h = -waveAtk_R[0].oriScale;
	}
	if (waveAtk_R[0].leftX >= 1920) {
		waveAtk_R[0].isAtk = 0;

	}
	for (int i = 1; i < kWaveNum; i++)
	{
		if (waveAtk_L[i].leftX >= waveAtk_L[i - 1].leftX + waveAtk_L[0].size.w) {	//先頭以後--左
			waveAtk_L[i].isAtk = 1;
		}
		if (waveAtk_L[i].isAtk == 1) {
			waveAtk_L[i].timer++;
			waveAtk_L[i].leftX -= waveAtk_L[i].spd;
			waveAtk_L[i].rightX -= waveAtk_L[i].spd;
		}
		if (waveAtk_L[i].timer >= waveAtk_L[i].maxTime) {
			waveAtk_L[i].scale_h = -waveAtk_L[i].oriScale;
		}
		if (waveAtk_L[i].rightX <= -waveAtk_L[0].size.w) {
			waveAtk_L[i].isAtk = 0;
			if (i == kWaveNum - 1 && waveAtk_R[i].isAtk == 0) {
				isAttack = false;
			}
		}

		if (waveAtk_R[i].leftX <= waveAtk_R[i - 1].leftX - waveAtk_R[0].size.w) {	//先頭以後--右
			waveAtk_R[i].isAtk = 1;
		}
		if (waveAtk_R[i].isAtk == 1) {
			waveAtk_R[i].timer++;
			waveAtk_R[i].leftX += waveAtk_R[i].spd;
			waveAtk_R[i].rightX += waveAtk_R[i].spd;
		}
		if (waveAtk_R[i].timer >= waveAtk_R[i].maxTime) {
			waveAtk_R[i].scale_h = -waveAtk_R[i].oriScale;
		}
		if (waveAtk_R[i].leftX >= 1920) {
			waveAtk_R[i].isAtk = 0;
			if (i == kWaveNum - 1 && waveAtk_L[i].isAtk == 0) {
				isAttack = false;
			}
		}
	}
	for (int i = 0; i < kWaveNum; i++) {
		if (waveAtk_L[i].topY >= waveAtk_L[i].maxHeight) {	//攻撃の高さの管理--左
			waveAtk_L[i].topY = waveAtk_L[i].maxHeight;
		}
		if (waveAtk_L[i].isAtk == 1 && waveAtk_L[i].topY >= waveAtk_L[i].size.h) {
			waveAtk_L[i].topY += waveAtk_L[i].scale_h;
		}

		if (waveAtk_R[i].topY >= waveAtk_R[i].maxHeight) {	//攻撃の高さの管理--右
			waveAtk_R[i].topY = waveAtk_R[i].maxHeight;
		}
		if (waveAtk_R[i].isAtk == 1 && waveAtk_R[i].topY >= waveAtk_R[i].size.h) {
			waveAtk_R[i].topY += waveAtk_R[i].scale_h;
		}
	}
}
