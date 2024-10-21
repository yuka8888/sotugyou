#pragma once
#include "Novice.h"
#include "mt.h"
class Player
{
public:
	void Initialize();

	void dicePhaseUpdate();

	void Draw();
private:
	Vector2 translation_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Vector2 acceleration = { 0, 5.0f };

	float kGround_ = 600.0f;

	bool isGround_ = false;

	Direction direction_ = Direction::kLeft;

	float kWidth_ = 36.0f;

	float kHeight_ = 36.0f;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
};

