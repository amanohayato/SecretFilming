#include "TutorialCommand.h"
#include "../../../Math/MathHelper.h"

void TutorialCommand::start()
{
	displayA_Push_ = false;
	displayY_Push_ = false;
	displayLT_Push_ = false;
	displayRT_Push_ = false;

	isCommandEnd_ = false;
	textBox_.Init();
	setText();
	textBox_.Display_Text(false);
	textBox_.Start_Text();

	onStart();
}

void TutorialCommand::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 10) % 360;

	textBox_.Update();

	onUpdate(deltaTime);
}

void TutorialCommand::draw() const
{
	onDraw();

	textBox_.Draw(textBoxPos_, FONT_ID::FONT_TEXT, textBoxSize_);

	if (displayA_Push_)
	{
		if (sinCount_ > 180.0f)
		{
			Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_A_PUSH_1, A_PushPos_, Vector2::Zero, Vector2(0.5f, 0.5f));
		}
		else
		{
			Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_A_PUSH_2, A_PushPos_, Vector2::Zero, Vector2(0.5f, 0.5f));
		}
	}

	if (displayY_Push_)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_Y_PUSH, A_PushPos_, Vector2::Zero, Vector2(0.5f, 0.5f));
	}

	if (displayLT_Push_)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LT_PUSH, A_PushPos_, Vector2::Zero, Vector2(0.5f, 0.5f));
	}

	if (displayRT_Push_)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RT_PUSH, A_PushPos_, Vector2::Zero, Vector2(0.5f, 0.5f));
	}

	if (displayY_Push_ || displayLT_Push_ || displayRT_Push_)
	{
		if (sinCount_ > 180.0f)
		{
			Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PUSH_ARROW, Push_Arrow_Pos_, Vector2::Zero, Vector2(0.5f, 0.5f));
		}
		else
		{
			Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PUSH_ARROW, Push_Arrow_Pos_ + Vector2(0.0f, 20.0f), Vector2::Zero, Vector2(0.5f, 0.5f));
		}
	}
}

void TutorialCommand::end()
{
	onEnd();
}
