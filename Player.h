#pragma once
#include "Novice.h"
#include "mt.h"
class Player
{
public:
	void Initialize();

	void Update();

	void Draw();
private:
	Vector2 translation_ = { 100.0f, 100.0f };

	Vector2 velocity_ = {};

	Direction direction_ = Direction::kLeft;

	float kWidth_ = 36.0f;

	float kHeight_ = 36.0f;

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
};

