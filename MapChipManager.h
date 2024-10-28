﻿#pragma once
#include "Input.h"
#include "string"
#include "assert.h"
#include "mt.h"

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

class MapChipManager
{
public:

	/// <summary>
	/// 読み込み済みのデータ削除
	/// </summary>
	void ResetMapChipData();

	/// <summary>
	/// ファイル読み込み
	/// </summary>
	/// <param name="filePath"></param>
	void LoadMapChipCsv(const std::string& filePath);


	uint32_t GetNumBlockVirtical();
	uint32_t GetNumBlockHorizontal();

	MapChipData GetMapChipDate();

	uint32_t GetBlockTopNum();
	uint32_t GetBlockBottomNum();

	uint32_t GetFallNum();

	Vector2 GetBlockSize();

	uint32_t GetWallNum();

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector2 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	IndexSet GetMapChipIndexSetByPosition(const Vector2& position);


private:
	//幅
	static inline const float kBlockWidth_ = 48.0f;
	//高さ
	static inline const float kBlockHeight_ = 48.0f;

	//縦の要素数
	static inline const uint32_t kNumBlockVirtical_ = 10;
	//横の要素数
	static inline const uint32_t kNumBlockHorizontal_ = 10;

	//ブロックの個数
	uint32_t kBlockTopNum_ = 0;
	uint32_t kBlockBottomNum_ = 0;

	//ブロックの個数
	uint32_t kFallNum_ = 0;

	//壁の個数
	uint32_t kWallNum_ = 0;

	MapChipData mapChipData_;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

};