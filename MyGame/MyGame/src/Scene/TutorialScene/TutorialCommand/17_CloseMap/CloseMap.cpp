#include "CloseMap.h"

CloseMap::CloseMap(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy)
{
	player_ = player;
	enemy_ = enemy;
}

void CloseMap::onStart()
{
	isWaitInput_ = false;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);
}

void CloseMap::onUpdate(float deltaTime)
{
	displayY_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (isWaitInput_)
	{
		displayY_Push_ = true;

		if (player_->getStateType() == Player_State_ID::Idle)
		{
			isCommandEnd_ = true;
		}
	}
	else
	{
		InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
		isWaitInput_ = true;
	}
}

void CloseMap::onDraw() const
{
}

void CloseMap::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);

	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);

	enemy_->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Idle), true);
	enemy_->set_is_event(true);
}

void CloseMap::setText()
{
	textBox_.add("TutorialText/17_CloseMap/CloseMap.txt");
}
