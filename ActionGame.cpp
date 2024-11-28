#include "ActionGame.h"

void ActionGame::Initialize()
{
	player_ = new Player;
	player_->Initialize();
	player_->SetTranslation(Vector2{ 50.0f, (float)kGroundPosition });

	actionGoalAABB.max = { actionGoalPosition.x + actionGoalSize.x / 2.0f, actionGoalPosition.y + actionGoalSize.y / 2.0f };
	actionGoalAABB.min = { actionGoalPosition.x - actionGoalSize.x / 2.0f, actionGoalPosition.y - actionGoalSize.y / 2.0f };
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

	player_->Draw();
}

bool ActionGame::IsClear()
{
	return isClear_;
}
