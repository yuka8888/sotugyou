#pragma once
#include "mt.h"
#include "time.h"
#include "random"
#include "Novice.h"

class Enemy
{
public:
	void Initialize();

	void Update();

	void Draw();

	void SetPlayerPosition(Vector2 playerPosition);

	Type GetType();


private:
	Vector2 position_ = {};

	Direction direction_ = Direction::kUp;

	Vector2 velocity_ = {};
	Vector2 size_ = { 32.0f, 32.0f };

	Vector2 playerPosition_ = {};

	unsigned int currentTime_;

	//攻撃タイプ
	Type type_ = Type::kNormal;

	void Move();

};

