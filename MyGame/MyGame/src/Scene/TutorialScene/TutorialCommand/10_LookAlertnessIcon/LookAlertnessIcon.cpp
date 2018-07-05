#include "LookAlertnessIcon.h"

LookAlertnessIcon::LookAlertnessIcon()
{
}

void LookAlertnessIcon::onStart()
{
	finalChangeAlpa_ = false;

	blindAlpa_ = 0.0f;

	afterBlindAlpa_ = 1.0f;

	blindAlpaChangeRate_ = 0.05f;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);



	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
}

void LookAlertnessIcon::onUpdate(float deltaTime)
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

	if (finalChangeAlpa_) isCommandEnd_ = true;

	displayA_Push_ = true;

	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
	{
		// セレクトSEを再生
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		finalChangeAlpa_ = true;

		afterBlindAlpa_ = 0.0f;

		blindAlpaChangeRate_ = -0.05f;
	}
}

void LookAlertnessIcon::onDraw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_MINI_ALERTNESS_ICON, Vector2::Zero, blindAlpa_);
}

void LookAlertnessIcon::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);



	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
}

void LookAlertnessIcon::setText()
{
	textBox_.add("TutorialText/10_LookAlertnessIcon/LookAlertnessIcon.txt");
}
