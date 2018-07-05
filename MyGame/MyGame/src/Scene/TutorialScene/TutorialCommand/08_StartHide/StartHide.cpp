#include "StartHide.h"

StartHide::StartHide(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy)
{
	player_ = player;
	enemy_ = enemy;
}

void StartHide::onStart()
{
	isWaitInput_ = false;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);


	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);

	tutorialAwareness_ = enemy_->get_awareness();
}

void StartHide::onUpdate(float deltaTime)
{
	tutorialAwareness_ += 0.1f;

	if (tutorialAwareness_ > 90.0f) tutorialAwareness_ = 90.0f;

	enemy_->set_awareness(tutorialAwareness_);

	displayA_Push_ = false;
	displayRT_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (isWaitInput_)
	{
		displayRT_Push_ = true;

		if (player_->getStateType() == Player_State_ID::EventAction)
		{
			isCommandEnd_ = true;
		}
	}
	else
	{
		if (textBox_.Get_Current_Text() < 1)
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
			textBox_.Increment_Text();

			InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
			isWaitInput_ = true;
		}
	}
}

void StartHide::onDraw() const
{
}

void StartHide::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);


	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);

	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
}

void StartHide::setText()
{
	textBox_.add("TutorialText/08_StartHide/StartHide_1.txt");
	textBox_.add("TutorialText/08_StartHide/StartHide_2.txt");
}
