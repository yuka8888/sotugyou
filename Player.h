﻿#pragma once
#include "Novice.h"
#include "mt.h"

class MapChipManager;

class Player
{
public:
	void Initialize();

	void dicePhaseUpdate();

	void Draw();

	void SetTranslation(Vector2 translation);

	void SetPaths(Direction paths);

	void SetMapChipPosition(IndexSet index);

	IndexSet GetMapChipPosition();

	void SetMapChipManager(MapChipManager* mapChipManager);

private:
	MapChipManager* mapChipManager_ = nullptr;

	Vector2 translation_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Vector2 acceleration = { 0, 5.0f };

	float kGround_ = 600.0f;

	bool isGround_ = false;

	Direction direction_ = Direction::kLeft;

	Direction paths_ = Direction::kNone;

	float kWidth_ = 36.0f;

	float kHeight_ = 36.0f;

	//プレイヤーのマップチップでの座標
	IndexSet mapChipPosition_;

	//サイコロの目
	int dice_ = 0;


	/// <summary>
	/// 移動
	/// </summary>
	void Move();


};

