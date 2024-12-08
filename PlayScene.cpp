#include "PlayScene.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	delete fade_;
}

void PlayScene::Initialize()
{
	//テクスチャの読み込み
	startBlockTexture_ = Novice::LoadTexture("./Resources/start.png");
	goalBlockTexture_ = Novice::LoadTexture("./Resources/goal.png");
	noneBlockTexture_ = Novice::LoadTexture("./Resources/blank.png");
	puzzleBlockTexture_ = Novice::LoadTexture("./Resources/puzzle.png");
	rouletteTexture_ = Novice::LoadTexture("./Resources/roulette.png");
	backGroundTexture_ = Novice::LoadTexture("./Resources/background.png");

	currentTime = (unsigned int)time(nullptr);
	srand(currentTime);

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	player_ = new Player;
	player_->Initialize();

	mapChipManager_ = new MapChipManager;

	actionGame_ = new ActionGame;
	actionGame_->Initialize();

	boss_ = new Boss;
	boss_->Initialize();

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
	kBlockHeight = mapChipManager_->GetBlockSize().y;
	kBlockWidth = mapChipManager_->GetBlockSize().x;

}

void PlayScene::Update()
{
	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

	fade_->Update();

	switch (phase_) {
		case Phase::dice:
			//サイコロをふる
			RollTheDice();

			player_->dicePhaseUpdate();

			break;
		case Phase::miniGame:
			actionGame_->Update();

			break;
		case Phase::boss:
			boss_->Update();
			player_->BossUpdate();

			//ボスとプレイヤーが当たったらダメージ
			if (isCollision(player_->GetAABB(), boss_->GetAABB()) && !player_->IsPreCollision()) {
				player_->SetHp(player_->GetHp() - 1);
				player_->IsCollision(true);
			}
			else if (isCollision(player_->GetAABB(), boss_->GetAABB())) {
				player_->IsCollision(true);
			}
			break;
	}

	//フェーズの切り替え
	ChangePhase();

	//サイコロを振っていないか
	if (dice_ == 0 && sugorokuTimer == 0.0f) {
	isRollDice = false;
	}

}

void PlayScene::Draw()
{
	int dice = (int)dice_;

	switch (phase_) {
		case Phase::dice:
			//背景
			Novice::DrawSprite(0, 0, backGroundTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			DrawMap();
			player_->Draw();
			Novice::DrawSprite(100, 550, rouletteTexture_, 1.0f, 1.0f, 0.0f, WHITE);


			ImGui::InputInt("dice", &dice);
			break;
		case Phase::miniGame:
			actionGame_->Draw();

			break;
		case Phase::boss:
			player_->Draw();
			boss_->Draw();
			break;
	}


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

				case MapChipType::kminiGame:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), puzzleBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

				case MapChipType::kAitem:
					Novice::DrawBox(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), int(kBlockWidth), int(kBlockHeight), 0.0f, RED, kFillModeSolid);
					break;

				case MapChipType::kNone:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), noneBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

				case MapChipType::kStart:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), startBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

				case MapChipType::kGoal:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), goalBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

			}

		}
	}


}

void PlayScene::RollTheDice()
{
	if (!isChoicePaths_) {
		//Aキーでサイコロを振る
		if (keys[DIK_A] && !preKeys[DIK_A] && (fade_->IsFinished() == true) && !isRollDice) {
			dice_ = rand() % 6 + 1;
			isRollDice = true;
		}

		//サイコロの値が1より大きい時
		if (dice_ > 0) {
			//上下左右でどこに進めるのか調べる
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex + 1) != MapChipType::kBlank) {
				if (prePaths_ != Direction::kDown) {
					paths_[pathsNum_] = Direction::kUp;
					pathsNum_++;
				}
			}
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex - 1) != MapChipType::kBlank) {
				if (prePaths_ != Direction::kUp) {
					paths_[pathsNum_] = Direction::kDown;
					pathsNum_++;
				}
			}
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex + 1, player_->GetMapChipPosition().yIndex) != MapChipType::kBlank) {
				if (prePaths_ != Direction::kLeft) {
					paths_[pathsNum_] = Direction::kRight;
					pathsNum_++;
				}
			}
			//if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex + 1, player_->GetMapChipPosition().yIndex) != MapChipType::kBlank) {
			//	if (prePaths_ != Direction::kRight) {
			//		paths_[pathsNum_] = Direction::kLeft;
			//		pathsNum_++;
			//	}
			//}

			//進める場所が一つなら移動させる
			if (pathsNum_ == 1) {
				player_->SetPaths(paths_[0]);
				dice_--;
				prePaths_ = paths_[0];

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
				prePaths_ = paths_[i];

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
				prePaths_ = paths_[i];

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
				prePaths_ = paths_[i];

				//初期化
				for (uint32_t j = 0; j < pathsNum_; j++) {
					paths_[j] = {};
				}
				pathsNum_ = 0;
				isChoicePaths_ = false;

			}
			//else if (paths_[i] == Direction::kLeft && keys[DIK_LEFTARROW]) {
			//	player_->SetPaths(paths_[i]);

			//	dice_--;
			//	prePaths_ = paths_[i];

			//	//初期化
			//	for (uint32_t j = 0; j < pathsNum_; j++) {
			//		paths_[j] = {};
			//	}
			//	pathsNum_ = 0;
			//	isChoicePaths_ = false;

			//}
		}
	}
	//サイコロの値プレイヤーが移動する

}

void PlayScene::ChangePhase()
{
	switch (phase_)
	{
		case PlayScene::Phase::dice:
			//フェーズをみにげーむに切り替え
			if (dice_ == 0 && isRollDice && mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex) == MapChipType::kminiGame) {
				if (sugorokuTimer < 1.0f) {
					sugorokuTimer += 0.03f;
				}
				else if (fade_->GetStatus() != Fade::Status::FadeOut) {
					fade_->Start(Fade::Status::FadeOut, 1.0f);
				}
				else if (fade_->IsFinished()) {
					fade_->Start(Fade::Status::FadeIn, 1.0f);
					phase_ = Phase::miniGame;
					actionGame_->Initialize();
					isRollDice = false;
					sugorokuTimer = 0.0f;
				}
			}
			//ゴールしたのでボス戦に切り替え
			if (mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex) == MapChipType::kGoal && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
				isGoal = true;
			}
			if (isGoal == true && (fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
				phase_ = Phase::boss;
				fade_->Start(Fade::Status::FadeIn, 1.0f);
			}

			break;
		case PlayScene::Phase::miniGame:
			//ミニゲームをクリアしたか
			if (actionGame_->IsClear() && fade_->GetStatus() != Fade::Status::FadeOut) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);

				//ランダムにステータス強化
				random_ = rand() % 3;

				if (random_ == 0) {
					player_->SetAttack(player_->GetAttack() + 1);
				}
				else if (random_ == 1) {
					player_->SetDefense(player_->GetDefense() + 1);
				}
				else {
					player_->SetHp(player_->GetHp() + 1);
				}

			}
			else if (fade_->GetStatus() == Fade::Status::FadeOut && fade_->IsFinished()) {
				phase_ = Phase::dice;
				delete actionGame_;
				actionGame_ = new ActionGame;
				fade_->Start(Fade::Status::FadeIn, 1.0f);
			}


			break;
		case PlayScene::Phase::boss:
			break;
		default:
			break;

	}


}
