#include "AlienWarning.h"

AlienWarning::AlienWarning(std::shared_ptr<TutorialEnemy> enemy)
{
	enemy_ = enemy;
}

void AlienWarning::onStart()
{
	finalChangeAlpa_ = false;

	blindAlpa_ = 0.0f;

	afterBlindAlpa_ = 1.0f;

	blindAlpaChangeRate_ = 0.05f;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);


	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);

	tutorialAwareness_ = 0.0f;

	enemy_->SetInactiveAwareness(false);
	enemy_->set_awareness(0.0f);
	enemy_->set_is_event(false);
}

void AlienWarning::onUpdate(float deltaTime)
{
	tutorialAwareness_ += 0.1f;

	switch (textBox_.Get_Current_Text())
	{
	case 0:
		if (tutorialAwareness_ > 30.0f) tutorialAwareness_ = 30.0f;
		break;

	case 1:
		if (tutorialAwareness_ > 60.0f) tutorialAwareness_ = 60.0f;
		break;

	case 2:
		if (tutorialAwareness_ > 90.0f) tutorialAwareness_ = 90.0f;
		break;
	}

	enemy_->set_awareness(tutorialAwareness_);

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

		if (textBox_.Get_Current_Text() < 2)
		{
			textBox_.Increment_Text();
		}
		else
		{
			finalChangeAlpa_ = true;

			afterBlindAlpa_ = 0.0f;

			blindAlpaChangeRate_ = -0.05f;
		}
	}
}

void AlienWarning::onDraw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_ALERTNESS_ICON, Vector2::Zero, blindAlpa_);
}

void AlienWarning::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);


	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
}

void AlienWarning::setText()
{
	textBox_.add("TutorialText/07_AlienWarning/AlienWarning_1.txt");
	textBox_.add("TutorialText/07_AlienWarning/AlienWarning_2.txt");
	textBox_.add("TutorialText/07_AlienWarning/AlienWarning_3.txt");
}
