﻿#pragma once
#include"Novice.h"
#include "algorithm"
#include"Vector4.h"
#include"Vector2.h"

class Fade {
public:
	// フェードの状態
	enum class Status {
		None,    // フェードなし
		FadeIn,  // フェードイン中
		FadeOut, // フェードアウト中
	};
	// 色
	unsigned int color = 0x0000000;

	unsigned int transparency;

	Vector2 size_ = { 100.0f, 100.0f };

	void Initialize();

	void Update();

	void Draw();

	void Start(Status status, float duration);

	void Stop();

	bool IsFinished() const;

	void SetSize(const Vector2& size);

	const Vector2& GetSize() const { return size_; }

	Status GetStatus();

private:

	int fadeTexture = Novice::LoadTexture("./Resources./fade.png");

	Status status_ = Status::None;

	// フェードの持続時間
	float duration_ = 0.0f;

	// 経過時間カウンター
	float counter_ = 0.0f;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;
};