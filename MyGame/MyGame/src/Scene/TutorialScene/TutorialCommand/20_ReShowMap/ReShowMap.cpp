#include "ReShowMap.h"

ReShowMap::ReShowMap(std::shared_ptr<Player> player)
{
	player_ = player;
}

void ReShowMap::onStart()
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

void ReShowMap::onUpdate(float deltaTime)
{
	blindAlpa_ += blindAlpaChangeRate_;

	bool isEndChangeAlpa = false;

	// •Ï‰»•‚ªƒvƒ‰ƒX‚È‚ç‚Î
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
		InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
		isWaitInput_ = true;
	}
}

void ReShowMap::onDraw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_MAP_ICON, Vector2::Zero, blindAlpa_);
}

void ReShowMap::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);



	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);


}

void ReShowMap::setText()
{
	textBox_.add("TutorialText/20_ReShowMap/ReShowMap.txt");
}
