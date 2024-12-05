#pragma once
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

	Vector2 GetBlockSize();

	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector2 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	IndexSet GetMapChipIndexSetByPosition(const Vector2& position);

	Vector2 GetStartPosition();

	uint32_t GetKNumBlockVirtical_();

	uint32_t GetKNumBlockHorizontal_();


private:
	//幅
	float kBlockWidth_ = 48.0f;
	//高さ
	float kBlockHeight_ = 48.0f;

	//縦の要素数
	static inline const uint32_t kNumBlockVirtical_ = 10;
	//横の要素数
	static inline const uint32_t kNumBlockHorizontal_ = 10;

	MapChipData mapChipData_;

	float kWindowHeight = 720.0f;
	float kWindowWidth = 1280.0f;

	//スタートの座標
	Vector2 startPosition_ = {};

};