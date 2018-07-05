#include "Running.h"

Running::Running(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy)
{
	player_ = player;
	enemy_ = enemy;
}

void Running::onStart()
{
	isWaitInput_ = false;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);



	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);


}

void Running::onUpdate(float deltaTime)
{
	displayA_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (isWaitInput_)
	{
		Vector3 playerPosition = player_->getPosition();

		Vector3 enemyPosition = enemy_->getPosition();

		float distance = Vector3::Distance(playerPosition, enemyPosition);

		if (player_->getStateType() != Player_State_ID::MapApp && distance < (16.5f * 3))
		{
			isCommandEnd_ = true;
		}
	}
	else
	{
		if (textBox_.Get_Current_Text() < 2)
		{
			displayA_Push_ = true;

			if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
			{
				// ƒZƒŒƒNƒgSE‚ðÄ¶
				Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);
				textBox_.Increment_Text();
			}
		}
		else
		{
			InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
			InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);
			InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
			isWaitInput_ = true;
		}
	}
}

void Running::onDraw() const
{
}

void Running::onEnd()
{
	player_->setCamera(false);
}

void Running::setText()
{
	textBox_.add("TutorialText/18_Running/Running_1.txt");
	textBox_.add("TutorialText/18_Running/Running_2.txt");
	textBox_.add("TutorialText/18_Running/Running_3.txt");
}
