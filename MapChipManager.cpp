﻿#include "MapChipManager.h"
#include <fstream>
#include <map>
#include <sstream>

namespace {
	std::map<std::string, MapChipType> mapChipTable = {
		{"0", MapChipType::kBlank},
		{"1", MapChipType::kShooting},
		{"2", MapChipType::kAitem},
		{"3", MapChipType::kNone},
		{"4", MapChipType::kStart},
		{"5", MapChipType::kGoal},
	};
}

void MapChipManager::ResetMapChipData()
{
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVirtical_);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {

		mapChipDataLine.resize(kNumBlockHorizontal_);
	}

}
void MapChipManager::LoadMapChipCsv(const std::string& filePath) {
	ResetMapChipData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップCSV
	std::stringstream mapChipCsv;
	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();
	// ファイルを閉じる
	file.close();

	std::string line;

	//すごろくのマスの大きさ
	kBlockHeight_ = kWindowHeight / kNumBlockVirtical_;
	kBlockWidth_ = kBlockHeight_;


	// CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumBlockVirtical_; ++i) {

		getline(mapChipCsv, line);

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal_; ++j) {

			std::string word;
			getline(line_stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[(i - kNumBlockVirtical_ + 1) * -1][j] = mapChipTable[word];

				//スタートの場所を取得
				if (mapChipTable[word] == MapChipType::kStart) {
					startPosition_ = GetMapChipPositionByIndex(j, i) - Vector2{-kBlockWidth_ / 2.0f, -kBlockHeight_ / 2.0f};
				}
			}


		}
	}
}



uint32_t MapChipManager::GetNumBlockVirtical()
{
	return kNumBlockVirtical_;
}

uint32_t MapChipManager::GetNumBlockHorizontal()
{
	return kNumBlockHorizontal_;
}

MapChipData MapChipManager::GetMapChipDate()
{
	return mapChipData_;
}

uint32_t MapChipManager::GetBlockTopNum()
{
	return kBlockTopNum_;
}

uint32_t MapChipManager::GetBlockBottomNum()
{
	return kBlockBottomNum_;
}

uint32_t MapChipManager::GetFallNum()
{
	return kFallNum_;
}

Vector2 MapChipManager::GetBlockSize()
{
	return { kBlockWidth_, kBlockHeight_ };
}

uint32_t MapChipManager::GetWallNum()
{
	return kWallNum_;
}

MapChipType MapChipManager::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	//範囲外なら空白にする
	if (xIndex < 0 || kNumBlockHorizontal_ - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumBlockVirtical_ - 1 < yIndex) {
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Rect MapChipManager::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	Vector2 center = GetMapChipPositionByIndex(xIndex, yIndex);

	Rect rect;

	rect.left = center.x - kBlockWidth_ / 2.0f;
	rect.right = center.x + kBlockWidth_ / 2.0f;
	rect.bottom = center.y - kBlockHeight_ / 2.0f;
	rect.top = center.y + kBlockWidth_ / 2.0f;

	return rect;
}

Vector2 MapChipManager::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return Vector2(kBlockWidth_ * xIndex, kBlockHeight_ * yIndex);
}

IndexSet MapChipManager::GetMapChipIndexSetByPosition(const Vector2& position) {
	IndexSet indexSet = {};
	indexSet.xIndex = uint32_t((position.x) / kBlockWidth_);
	float ypos = (position.y + kBlockHeight_ / 2.0f);
	float yIndex = (ypos / kBlockHeight_);
	indexSet.yIndex = uint32_t(yIndex);
	return indexSet;
}

Vector2 MapChipManager::GetStartPosition()
{
	return startPosition_;
}
