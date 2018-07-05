#include "EndHide.h"

EndHide::EndHide(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy)
{
	player_ = player;
	enemy_ = enemy;
}

void EndHide::onStart()
{
	isWaitInput_ = false;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);

	

	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);

	enemy_->changeTimer(2.0f);
	enemy_->setStopTimer(2.0f);
}

void EndHide::onUpdate(float deltaTime)
{
	displayRT_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (isWaitInput_)
	{
		displayRT_Push_ = true;

		if (player_->getStateType() == Player_State_ID::Event_After)
		{
			isCommandEnd_ = true;
		}
	}
	else
	{
		InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
		isWaitInput_ = true;
	}
}

void EndHide::onDraw() const
{
}

void EndHide::onEnd()
{
	enemy_->SetInactiveAwareness(true);

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);

	

	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);


}

void EndHide::setText()
{
	textBox_.add("TutorialText/11_EndHide/EndHide.txt");
}
