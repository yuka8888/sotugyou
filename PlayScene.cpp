#include "PlayScene.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	delete shooting_;
	delete puzzle_;
	delete player_;
	delete fade_;
}

void PlayScene::Initialize()
{
	//テクスチャの読み込み
	startBlockTexture_ = Novice::LoadTexture("./Resources/start.png");
	goalBlockTexture_ = Novice::LoadTexture("./Resources/goal.png");
	noneBlockTexture_ = Novice::LoadTexture("./Resources/blank.png");
	puzzleBlockTexture_ = Novice::LoadTexture("./Resources/puzzle.png");
	actionBlockTexture_ = Novice::LoadTexture("./Resources/enemyicon.png");
	itemBlockTexture_ = Novice::LoadTexture("./Resources/itemicon.png");
	rouletteTexture_[0] = Novice::LoadTexture("./Resources/roulette1.png");
	rouletteTexture_[1] = Novice::LoadTexture("./Resources/roulette2.png");
	rouletteTexture_[2] = Novice::LoadTexture("./Resources/roulette3.png");
	rouletteTexture_[3] = Novice::LoadTexture("./Resources/roulette4.png");
	rouletteTexture_[4] = Novice::LoadTexture("./Resources/roulette5.png");
	rouletteTexture_[5] = Novice::LoadTexture("./Resources/roulette6.png");
	rouletteTexture_[6] = Novice::LoadTexture("./Resources/roulette7.png");
	backGroundTexture_ = Novice::LoadTexture("./Resources/background.png");
	upArrowTexture_ = Novice::LoadTexture("./Resources/arrow.png");
	downArrowTexture_ = Novice::LoadTexture("./Resources/arrowr3.png");
	rightArrowTexture_ = Novice::LoadTexture("./Resources/arrowr2.png");
	gameOverTexture_ = Novice::LoadTexture("./Resources/shooting_bg2.png");
	aTexture_ = Novice::LoadTexture("./Resources/Sprite-0031.png");
	attackUpTexture_ = Novice::LoadTexture("./Resources/ATKUPicon.png");
	puzzle_ = new Puzzle;
	puzzle_->Initialize();

	shooting_ = new Shooting;
	shooting_->Initialize();

	currentTime_ = (unsigned int)time(nullptr);
	srand(currentTime_);

	fade_ = new Fade();
	fade_->Initialize();

	fade_->Start(Fade::Status::FadeIn, 1.0f);

	player_ = new Player;
	player_->Initialize();

	mapChipManager_ = new MapChipManager;

	actionGame_ = new ActionGame;
	actionGame_->Initialize();

	switch (phase_)
	{
		case PlayScene::Phase::dice:
			//マップの取得
			mapChipManager_->LoadMapChipCsv("Resources/map.csv");
			//playerの初期位置の取得
			player_->SetPosition(mapChipManager_->GetStartPosition());

			break;
		case PlayScene::Phase::action:
			break;
		case PlayScene::Phase::pazzle:
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

			if (timer >= 1.0f && isClear) {
				isClear = false;
				timer = 0.0f;
			}
			else if (isClear) {
				timer += 0.01f;
			}

			break;

		case Phase::action:
			Action();

			break;
			

		case Phase::pazzle:
			puzzle_->Update();

			break;
		case Phase::boss:
			shooting_->Update();

			if (shooting_->IsClear() && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
			}

			if (shooting_->IsClear() && (fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
				sceneNo = kClear;
			}

			if (shooting_->IsGameOver() && fade_->IsFinished() && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
				isGameOver = true;
			}

			if (isGameOver && keys[DIK_SPACE] && !(fade_->GetStatus() == Fade::Status::FadeOut)) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
			}
			if (isGameOver && (fade_->GetStatus() == Fade::Status::FadeOut) && (fade_->IsFinished() == true)) {
				sceneNo = kTitle;
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
			Novice::DrawSpriteRect(250, 550, 0, 0, 32, 32, aTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			player_->Draw();

			//ルーレット
			if (dice_ == diceAnimation_ && int(sugorokuTimer / 0.5f) % 2 == 1) {
				Novice::DrawSprite(100, 550, rouletteTexture_[0], 1.0f, 1.0f, 0.0f, WHITE);
			}
			else {
				Novice::DrawSprite(100, 550, rouletteTexture_[dice], 1.0f, 1.0f, 0.0f, WHITE);
			}
			ImGui::InputInt("dice", &dice);

			if (isClear) {
				Novice::DrawSprite(1280 / 2 - 96, 720 / 2 - 96, attackUpTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			break;
		case Phase::action:
			actionGame_->Draw();
			player_->Draw();
			for (int i = 0; i < player_->GetHp(); i++) {
				Novice::DrawSprite(i * 70, 5, LifeTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}

			break;
		case Phase::pazzle:
			puzzle_->Draw();

			break;
		case Phase::boss:
			shooting_->Draw();

			for (int i = 0; i < player_->GetHp(); i++) {
				Novice::DrawSprite(i * 70, 5, LifeTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			break;
	}

	if (isGameOver) {
		Novice::DrawSprite(0, 0, gameOverTexture_, 1.0f, 1.0f, 0.0f, WHITE);
	}
	fade_->Draw();

}

void PlayScene::Action()
{

	//アクションゲーム
	actionGame_->Update();
	player_->ActionGameUpdate();

	actionGame_->SetPlayerPosition(player_->GetPosition());

	//ボスとプレイヤーが当たったらダメージ
	if (isCollision(player_->GetAABB(), actionGame_->GetAABB()) && !player_->IsPreCollision()) {
		player_->SetHp(player_->GetHp() - 1);
		player_->IsCollision(true);
	}
	else if (isCollision(player_->GetAABB(), actionGame_->GetAABB())) {
		player_->IsCollision(true);
	}
	//ボスの弾とプレイヤーが当たったらダメージ
	if (isCollision(player_->GetAABB(), actionGame_->GetBulletAABB()) && !player_->IsPreCollision()) {
		player_->SetHp(player_->GetHp() - 1);
		player_->IsCollision(true);
	}
	else if (isCollision(player_->GetAABB(), actionGame_->GetBulletAABB())) {
		player_->IsCollision(true);
	}
	//ボスとプレイヤーの弾が当たったらダメージ
	for (int i = 0; i < player_->GetBulletNum(); i++) {
		if (player_->IsBulletDraw(i)) {
			if (isCollision(player_->GetBulletAABB(i), actionGame_->GetAABB()) && !actionGame_->IsPreCollision()) {
				actionGame_->SetHp(actionGame_->GetHp() - player_->GetAttack());
				actionGame_->IsCollision(true);
			}
			else if (isCollision(player_->GetBulletAABB(i), actionGame_->GetAABB())) {
				actionGame_->IsCollision(true);
			}
		}
	}

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

				case MapChipType::kPazzle:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), puzzleBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

				case MapChipType::kAction:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), actionBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
					break;

				case MapChipType::kAitem:
					Novice::DrawSprite(int(j * kBlockWidth), int((numBlockVirtical - i - 1) * kBlockHeight), itemBlockTexture_, 1.0f, 1.0f, 0.0f, WHITE);
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

	if (isChoicePaths_) {
		//分かれ道の矢印描画
		for (uint32_t i = 0; i < pathsNum_; i++) {
			if (paths_[i] == Direction::kDown) {
				Novice::DrawSprite((int)mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex).x, (int)(mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex, (numBlockVirtical - player_->GetMapChipPosition().yIndex))).y, downArrowTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			if (paths_[i] == Direction::kUp) {
				Novice::DrawSprite((int)mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex).x, (int)(mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex, (numBlockVirtical - player_->GetMapChipPosition().yIndex) - 2)).y, upArrowTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
			if (paths_[i] == Direction::kRight) {
				Novice::DrawSprite((int)mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex + 1, player_->GetMapChipPosition().yIndex).x, (int)(mapChipManager_->GetMapChipPositionByIndex(player_->GetMapChipPosition().xIndex, (numBlockVirtical - player_->GetMapChipPosition().yIndex) - 1)).y, rightArrowTexture_, 1.0f, 1.0f, 0.0f, WHITE);
			}
		}
	}
}

void PlayScene::RollTheDice()
{
	if (!isChoicePaths_) {
		//Aキーでサイコロを振る
		if (keys[DIK_A] && !preKeys[DIK_A] && (fade_->IsFinished() == true) && !isRollDice && dice_ == 0) {
			dice_ = rand() % 6 + 1;
			diceAnimation_ = dice_;
			isDiceAnimation_ = true;
			sugorokuTimerAdd_ = 0.2f;
			sugorokuAnimationNum_ = 0;
		}

		//ルーレットのアニメーション
		if (isDiceAnimation_) {
			sugorokuTimer += sugorokuTimerAdd_;
			if (sugorokuTimer >= 0.5f && sugorokuAnimationNum_ <= 10) {
				sugorokuTimer = 0.0f;
				sugorokuAnimationNum_ += 1;
				//ルーレットを１づつ変えてアニメーション
				dice_ += 1;
				if (dice_ > 6) {
					dice_ = 1;
				}
			}
			else if (sugorokuTimer >= 0.5f && sugorokuTimerAdd_ <= 0.02f && diceAnimation_ == dice_) {
				isRollDice = true;
				sugorokuAnimationNum_ = 0;
				sugorokuTimer = 0.0f;
				isDiceAnimation_ = false;
			}
			else if (sugorokuTimer >= 0.5f && sugorokuAnimationNum_ > 10) {
				sugorokuTimer = 0.0f;
				sugorokuAnimationNum_ += 1;
				if (sugorokuTimerAdd_ >= 0.01f) {
					sugorokuTimerAdd_ -= 0.01f;
				}
				//ルーレットを１づつ変えてアニメーション
				dice_ += 1;
				if (dice_ > 6) {
					dice_ = 1;
				}
			}
		}

		//サイコロの値が1より大きい時
		if (dice_ > 0 && !isDiceAnimation_) {
			if (pathsNum_ == 0) {
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
			}

			//進める場所が一つなら移動させる
			if (dice_ == diceAnimation_ && sugorokuTimer < 3.5f) {
				sugorokuTimer += 0.03f;
			}
			else if (dice_ != diceAnimation_ && sugorokuTimer < 1.0f) {
				sugorokuTimer += 0.03f;
			}
			else if (pathsNum_ == 1) {
				player_->SetPaths(paths_[0]);
				dice_--;
				prePaths_ = paths_[0];

				//初期化
				for (uint32_t i = 0; i < pathsNum_; i++) {
					paths_[i] = {};
				}
				pathsNum_ = 0;
				sugorokuTimer = 0.0f;
			}
			else {
				//複数あるときは選ばせる
				isChoicePaths_ = true;
				sugorokuTimer = 0.0f;
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
			//フェーズをパズルに切り替え
			if (dice_ == 0 && isRollDice && mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex) == MapChipType::kPazzle) {
				if (sugorokuTimer < 1.0f) {
					sugorokuTimer += 0.03f;
				}
				else if (fade_->GetStatus() != Fade::Status::FadeOut) {
					fade_->Start(Fade::Status::FadeOut, 1.0f);
				}
				else if (fade_->IsFinished()) {
					fade_->Start(Fade::Status::FadeIn, 1.0f);
					phase_ = Phase::pazzle;
					actionGame_->Initialize();
					isRollDice = false;
					sugorokuTimer = 0.0f;
				}
			}
			//フェーズをアクションに切り替え
			if (dice_ == 0 && isRollDice && mapChipManager_->GetMapChipTypeByIndex(player_->GetMapChipPosition().xIndex, player_->GetMapChipPosition().yIndex) == MapChipType::kAction) {
				if (sugorokuTimer < 1.0f) {
					sugorokuTimer += 0.03f;
				}
				else if (fade_->GetStatus() != Fade::Status::FadeOut) {
					fade_->Start(Fade::Status::FadeOut, 1.0f);
				}
				else if (fade_->IsFinished()) {
					fade_->Start(Fade::Status::FadeIn, 1.0f);
					phase_ = Phase::action;
					prePlayerPosition_ = player_->GetPosition();
					player_->SetPosition({ 150.0f, 500.0f });
					player_->SetHp(player_->GetMaxHp());
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
		case PlayScene::Phase::action:
			//アクションをクリアしたか
			if (actionGame_->IsClear() && fade_->GetStatus() != Fade::Status::FadeOut) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
				isClear = true;

				//ランダムにステータス強化
				player_->SetAttackUpNum_(player_->GetAttackUpNum_() + 1);

			}
			//アクションをクリアできなかった
			if (player_->GetHp() <= 0 && (fade_->GetStatus() != Fade::Status::FadeOut)) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);

			}
			else if (fade_->GetStatus() == Fade::Status::FadeOut && fade_->IsFinished()) {
				phase_ = Phase::dice;
				delete actionGame_;
				actionGame_ = new ActionGame;
				actionGame_->Initialize();
				player_->SetPosition(prePlayerPosition_);
				for (int i = 0; i < player_->GetBulletNum(); i++) {
					player_->IsBulletDraw(false, i);
				}
				fade_->Start(Fade::Status::FadeIn, 1.0f);
			}


			break;
		case PlayScene::Phase::pazzle:
			//パズルをクリアしたか
			if (puzzle_->IsClear() && fade_->GetStatus() != Fade::Status::FadeOut) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
				isClear = true;

				//ランダムにステータス強化
				player_->SetAttackUpNum_(player_->GetAttackUpNum_() + 1);

			}
			//パズルをクリアできなかった
			if (puzzle_->IsGameOver() && fade_->GetStatus() != Fade::Status::FadeOut) {
				fade_->Start(Fade::Status::FadeOut, 1.0f);
			}
			else if (fade_->GetStatus() == Fade::Status::FadeOut && fade_->IsFinished()) {
				phase_ = Phase::dice;
				delete puzzle_;
				puzzle_ = new Puzzle;
				puzzle_->Initialize();
				fade_->Start(Fade::Status::FadeIn, 1.0f);
			}

			break;
		case PlayScene::Phase::boss:
			break;
		default:
			break;

	}


}
