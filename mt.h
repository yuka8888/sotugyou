﻿#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "math.h"
#include "assert.h"

enum class MapChipType {
	kBlank,//空白
	kShooting,//シューティングゲーム
	kAitem, //アイテムもらえる
	kNone, //特になし
	kStart, //スタート
	kGoal, //ゴール
};

enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};

struct Matrix3x3 final {
	float m[3][3];
};

struct Vertex final {
	float left;
	float right;
	float top;
	float bottom;
};

struct VertexPosition final {
	float left;
	float right;
	float top;
	float bottom;
};

struct Camera final {
	Vertex vertex;
	Matrix3x3 worldMatrix;
	Vector2 viewPortPosition;
	Vector2 viewPortSize;

};

struct AABB {
	Vector2 min{};
	Vector2 max{};
};

struct Block {
	AABB aabb_;
	Vector2 initialPosition;
	Vector2 velocity;
	bool isFall = false;
};

enum Direction {
	kRight,
	kLeft,
	kUp,
	kDown,
	kNone,
};


struct IndexSet {
	int xIndex;
	int yIndex;
};

Vector2 operator+(Vector2 num1, Vector2 num2);

Vector2 operator-(Vector2 num1, Vector2 num2);

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 MakeRotateMatrix3x3(float theta);

Matrix3x3 MakeTransLateMatrix(Vector2 translate);

Matrix3x3 MakeScaleMatrix(Vector2 scale);

Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

Matrix3x3 MakewvpVpMatrix(Matrix3x3 worldMatrix, Matrix3x3 cameraWorldMatrix, Vertex vertex, Vector2 viewPortPosition, Vector2 viewPortSize);

Matrix3x3 MakevpVpMatrix(Matrix3x3 worldMatrix, Vertex vertex, Vector2 viewPortPosition, Vector2 viewPortSize);

bool isCollision(const AABB& aabb1, const AABB& aabb2);

bool isCollision(const AABB& aabb, const Vector2& position);

float easeInCubic(float x);

/// <summary>
/// 線形補間
/// </summary>
/// <param name="a">始点</param>
/// <param name="b">終点</param>
/// <param name="t"></param>
/// <returns></returns>
float Lerp(const float& a, const float& b, float t);