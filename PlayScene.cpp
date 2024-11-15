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
	currentTime = (unsigned int)time(nullptr);
	srand(currentTime);

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	player_ = new Player;
	player_->Initialize();

	mapChipManager_ = new MapChipManager;

	switch (phase_)
	{
		case PlayScene::Phase::dice:
			//マップの取得
			mapChipManager_->LoadMapChipCsv("Resources/map.csv");
			//playerの初期位置の取得
			player_->SetTranslation(mapChipManager_->GetStartPosition());

			break;
		case PlayScene::Phase::miniGame:
			break;
		case PlayScene::Phase::boss:
			break;
		default:
			break;
	}

	player_->SetMapChipManager(mapChipManager_);

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

			//サイコロをふる
			RollTheDice();

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
					Novice::DrawBox(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), int(kBlockWidth), int(kBlockHeight), 0.0f, BLACK, kFillModeSolid);
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

void PlayScene::RollTheDice()
{
	if (!isChoicePaths_) {
		//Aキーでサイコロを振る
		if (keys[DIK_A] && !preKeys[DIK_A]) {
			dice_ = rand() % 6 + 1;
		}

		//サイコロの値が1より大きい時
		if (dice_ > 0) {
			//上下左でどこに進めるのか調べる
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, (player_->GetMapChipPosition().yIndex - 10 - 1) * -1) != MapChipType::kBlank) {
				paths_[pathsNum_] = Direction::kDown;
				pathsNum_++;
			}
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, (player_->GetMapChipPosition().yIndex - 10 + 1) * -1) != MapChipType::kBlank) {
				paths_[pathsNum_] = Direction::kUp;
				pathsNum_++;
			}
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex + 1, (player_->GetMapChipPosition().yIndex - 10) * -1) != MapChipType::kBlank) {
				paths_[pathsNum_] = Direction::kRight;
				pathsNum_++;
			}

			//進める場所が一つなら移動させる
			if (pathsNum_ == 1) {
				player_->SetPaths(paths_[0]);
				dice_--;

				//初期化
				for (uint32_t i = 0; i < pathsNum_; i++) {
					paths_[i] = {};
				}
				pathsNum_ = 0;
			}
			else {
				//複数あるときは選ばせる
				isChoicePaths_ = true;
			}

		}
	}
	//道を選び中
	else {
		for (uint32_t i = 0; i < pathsNum_; i++) {
			if (paths_[i] == Direction::kDown && keys[DIK_DOWNARROW]) {
				player_->SetPaths(paths_[i]);

				dice_--;

				//初期化
				for (uint32_t j = 0; j < pathsNum_; j++) {
					paths_[j] = {};
				}
				pathsNum_ = 0;
				isChoicePaths_ = false;

			}
			else if (paths_[i] == Direction::kUp && keys[DIK_UPARROW]) {
				player_->SetPaths(paths_[i]);

				dice_--;

				//初期化
				for (uint32_t j = 0; j < pathsNum_; j++) {
					paths_[j] = {};
				}
				pathsNum_ = 0;
				isChoicePaths_ = false;

			}
			else if (paths_[i] == Direction::kRight && keys[DIK_RIGHTARROW]) {
				player_->SetPaths(paths_[i]);

				dice_--;

				//初期化
				for (uint32_t j = 0; j < pathsNum_; j++) {
					paths_[j] = {};
				}
				pathsNum_ = 0;
				isChoicePaths_ = false;

			}
		}
	}
	//サイコロの値プレイヤーが移動する

}
