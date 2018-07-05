#include "TutorialStart.h"

TutorialStart::TutorialStart(std::shared_ptr<TutorialEnemy> enemy)
{
	enemy_ = enemy;
}

void TutorialStart::onStart()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);

	enemy_->initialize(); 
	enemy_->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Idle), true);
	enemy_->set_is_event(true);
	enemy_->changeSpeed(1.0f, 1.5f);
	enemy_->changeRandomEventFlag(false);
	enemy_->setTutorialMovePoint();
	enemy_->SetInactiveAwareness(true);
}

void TutorialStart::onUpdate(float deltaTime)
{
	displayA_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	displayA_Push_ = true;

	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
	{
		// ÉZÉåÉNÉgSEÇçƒê∂
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		if (textBox_.Get_Current_Text() < 2)
		{
			textBox_.Increment_Text();
		}
		else
		{
			isCommandEnd_ = true;
		}
	}
}

void TutorialStart::onDraw() const
{
	
}

void TutorialStart::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
}

void TutorialStart::setText()
{
	textBox_.add("TutorialText/01_TutorialStart/TutorialStart_1.txt");
	textBox_.add("TutorialText/01_TutorialStart/TutorialStart_2.txt");
	textBox_.add("TutorialText/01_TutorialStart/TutorialStart_3.txt");
}
