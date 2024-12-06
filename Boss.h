#pragma once
#include "mt.h"
#include "Novice.h"

class Boss
{
public:
	Boss();

	~Boss();

	void Initialize();

	void Update();

private:
	//攻撃しているか
	bool isAttack = false;

	//体力
	int hp = 100;

	static const int kWaveNum = 10;

	Attack waveAtk_R[kWaveNum] = {};
	Attack waveAtk_L[kWaveNum] = {};
	
	void WaveAtk();

};

