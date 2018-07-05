#include "ShowMap.h"

ShowMap::ShowMap(std::shared_ptr<Player> player)
{
	player_ = player;
}

void ShowMap::onStart()
{
	isWaitInput_ = false;

	finalChangeAlpa_ = false;

	blindAlpa_ = 0.0f;

	afterBlindAlpa_ = 1.0f;

	blindAlpaChangeRate_ = 0.05f;

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);

	

	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);


}

void ShowMap::onUpdate(float deltaTime)
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
	displayY_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (finalChangeAlpa_) isCommandEnd_ = true;

	if (isWaitInput_)
	{
		displayY_Push_ = true;

		if (player_->getStateType() == Player_State_ID::MapApp)
		{
			InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);

			finalChangeAlpa_ = true;

			afterBlindAlpa_ = 0.0f;

			blindAlpaChangeRate_ = -0.05f;
		}
	}
	else
	{
		if (textBox_.Get_Current_Text() < 1)
		{
			displayA_Push_ = true;

			if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
			{
				// セレクトSEを再生
				Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

				textBox_.Increment_Text();
			}
		}
		else
		{
			textBox_.Increment_Text();

			InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
			isWaitInput_ = true;
		}
	}
}

void ShowMap::onDraw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_MAP_ICON, Vector2::Zero, blindAlpa_);
}

void ShowMap::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);

	

	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);


}

void ShowMap::setText()
{
	textBox_.add("TutorialText/13_ShowMap/ShowMap_1.txt");
	textBox_.add("TutorialText/13_ShowMap/ShowMap_2.txt");
}
