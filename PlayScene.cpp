#include "PlayScene.h"

PlayScene::PlayScene()
{
	delete fade_;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	player_ = new Player;
	player_->Initialize();

	mapChipManager_ = new MapChipManager;

	switch (phase_)
	{
		case PlayScene::Phase::dice:
			mapChipManager_->LoadMapChipCsv("Resources/map.csv");
			break;
		case PlayScene::Phase::miniGame:
			break;
		case PlayScene::Phase::boss:
			break;
		default:
			break;
	}

	//すごろくのマスの大きさ
	kBlockHeight = kWindowHeight / mapChipManager_->GetNumBlockVirtical();
	kBlockWidth = kBlockHeight;
}

void PlayScene::Update()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	fade_->Update();

	switch (phase_) {
		case Phase::dice:
			player_->dicePhaseUpdate();

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				dice = rand() % 6 + 1;
			}
			break;
		case Phase::miniGame:
			break;
		case Phase::boss:
			break;
	}

	if (Novice::CheckHitKey(DIK_SPACE) && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
		fade_->Start(Fade::Status::FadeOut, 1.0f);
	}

	if ((fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
		sceneNo = kClear;
	}

}

void PlayScene::Draw()
{
	DrawMap();

	player_->Draw();
	fade_->Draw();

}

void PlayScene::DrawMap()
{
	// 要素数
	uint32_t numBlockVirtical = mapChipManager_->GetNumBlockVirtical();
	uint32_t numBlockHorizonal = mapChipManager_->GetNumBlockHorizontal();

	for (uint32_t i = 0; i < numBlockVirtical; i++) {
		for (uint32_t j = 0; j < numBlockHorizonal; j++) {


			switch (mapChipManager_->GetMapChipDate().data[i][j]) {
				case MapChipType::kBlank:
					break;

				case MapChipType::kShooting:
					Novice::DrawBox(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), int(kBlockWidth), int(kBlockHeight), 0.0f, BLUE, kFillModeSolid);
					break;

				case MapChipType::kAitem:
					Novice::DrawBox(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), int(kBlockWidth), int(kBlockHeight), 0.0f, RED, kFillModeSolid);
					break;

				case MapChipType::kNone:
					Novice::DrawBox(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), int(kBlockWidth), int(kBlockHeight), 0.0f, WHITE, kFillModeSolid);
					break;

			}

		}
	}


}
