#include "Hiding.h"

Hiding::Hiding(std::shared_ptr<TutorialEnemy> enemy)
{
	enemy_ = enemy;
}

void Hiding::onStart()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);

	
	
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
}

void Hiding::onUpdate(float deltaTime)
{
	enemy_->changeTimer(0.1f);

	displayA_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	displayA_Push_ = true;

	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
	{
		// ÉZÉåÉNÉgSEÇçƒê∂
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		isCommandEnd_ = true;
	}
}

void Hiding::onDraw() const
{
}

void Hiding::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);

	
	
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);

}

void Hiding::setText()
{
	textBox_.add("TutorialText/09_Hiding/Hiding.txt");
}
