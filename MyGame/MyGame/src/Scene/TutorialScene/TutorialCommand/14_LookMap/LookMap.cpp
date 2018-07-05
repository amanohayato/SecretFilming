#include "LookMap.h"

LookMap::LookMap(std::shared_ptr<TutorialEnemy> enemy)
{
	enemy_ = enemy;
}

void LookMap::onStart()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);

	enemy_->set_is_event(false);
	enemy_->setStopTimer(2.5f);
}

void LookMap::onUpdate(float deltaTime)
{
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

void LookMap::onDraw() const
{
}

void LookMap::onEnd()
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

void LookMap::setText()
{
	textBox_.add("TutorialText/14_LookMap/LookMap.txt");
}
