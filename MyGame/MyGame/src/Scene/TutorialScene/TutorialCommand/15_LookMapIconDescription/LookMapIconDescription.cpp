#include "LookMapIconDescription.h"

LookMapIconDescription::LookMapIconDescription(std::shared_ptr<TutorialEnemy> enemy)
{
	enemy_ = enemy;
}

void LookMapIconDescription::onStart()
{
	finalChangeAlpa_ = false;

	blindAlpa_ = 0.0f;

	afterBlindAlpa_ = 1.0f;

	blindAlpaChangeRate_ = 0.05f;

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

void LookMapIconDescription::onUpdate(float deltaTime)
{
	blindAlpa_ += blindAlpaChangeRate_;

	bool isEndChangeAlpa = false;

	// 変化幅がプラスならば
	if (blindAlpaChangeRate_ > 0)
	{
		if (blindAlpa_ < afterBlindAlpa_) return;
		blindAlpa_ = afterBlindAlpa_;
	}
	else
	{
		if (blindAlpa_ > afterBlindAlpa_) return;
		blindAlpa_ = afterBlindAlpa_;
	}

	displayA_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	displayA_Push_ = true;

	if (finalChangeAlpa_) isCommandEnd_ = true;

	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
	{
		// セレクトSEを再生
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		finalChangeAlpa_ = true;

		afterBlindAlpa_ = 0.0f;

		blindAlpaChangeRate_ = -0.05f;
	}
}

void LookMapIconDescription::onDraw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_MAP_ICON_DESCRIPTION, Vector2::Zero, blindAlpa_);
}

void LookMapIconDescription::onEnd()
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

void LookMapIconDescription::setText()
{
	textBox_.add("TutorialText/15_LookMapIconDescription/LookMapIconDescription.txt");
}
