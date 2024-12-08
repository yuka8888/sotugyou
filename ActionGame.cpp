#include "ActionGame.h"

void ActionGame::Initialize()
{
	player_ = new Player;
	player_->Initialize();
	player_->SetTranslation(Vector2{ 50.0f, (float)kGroundPosition });

	actionGoalAABB.max = { actionGoalPosition.x + actionGoalSize.x / 2.0f, actionGoalPosition.y + actionGoalSize.y / 2.0f };
	actionGoalAABB.min = { actionGoalPosition.x - actionGoalSize.x / 2.0f, actionGoalPosition.y - actionGoalSize.y / 2.0f };
	actionScaffoldPosition[0] = { 200,550 };
	actionScaffoldPosition[1] = { 400,450 };
	actionScaffoldPosition[2] = { 600,350 };

	for (int i = 0; i < 3; i++) {
		actionScaffoldAABB[i].max = { actionScaffoldPosition[i].x + actionScaffoldSize.x / 2.0f,actionScaffoldPosition[i].y + actionScaffoldSize.y / 2.0f };
		actionScaffoldAABB[i].min = { actionScaffoldPosition[i].x - actionScaffoldSize.x / 2.0f,actionScaffoldPosition[i].y - actionScaffoldSize.y / 2.0f };
	}
}

void ActionGame::Update()
{
	player_->ActionGameUpdate();

	
	if (isCollision(player_->GetAABB(), actionGoalAABB)) {
		isClear_ = true;
	}
}

void ActionGame::Draw()
{
	Novice::DrawBox(0, kGroundPosition, (int)kWindowWidth, 200, 0.0f, GREEN, kFillModeSolid);

	Novice::DrawBox((int)actionGoalPosition.x, (int)actionGoalPosition.y, (int)actionGoalSize.x, (int)actionGoalSize.y, 0.0f, RED, kFillModeSolid);
	
	for (int i = 0; i < 3; i++) {
		Novice::DrawBox((int)actionScaffoldPosition[i].x, (int)actionScaffoldPosition[i].y, (int)actionScaffoldSize.x, (int)actionScaffoldSize.y, 0.0f, WHITE,kFillModeSolid);
	}
	player_->Draw();
}

bool ActionGame::IsClear()
{
	return isClear_;
}
