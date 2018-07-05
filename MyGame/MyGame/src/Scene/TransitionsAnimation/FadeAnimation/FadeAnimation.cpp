#include "FadeAnimation.h"

FadeAnimation::FadeAnimation(float maxAnimeTime)
{
	maxAnimeTime_ = maxAnimeTime;
}

void FadeAnimation::start()
{
	isEnd_ = false;
	canUpdateScene_ = false;
	isAnimeReturn_ = false;
	fadeRate_ = 0.0f;
	animeTimer_ = 0.0f;
}

void FadeAnimation::update(float deltaTime)
{
	animeTimer_ += deltaTime;

	// �P�܂�Ԃ��O
	if (!isAnimeReturn_)
	{
		fadeRate_ = (float)(animeTimer_ / maxAnimeTime_);

		if (animeTimer_ > maxAnimeTime_)
		{
			animeTimer_ = 0;
			isAnimeReturn_ = true;

			canUpdateScene_ = true;

			isChangeScene_ = true;
		}
	}
	else
	{
		fadeRate_ = 1.0f - (float)(animeTimer_ / maxAnimeTime_);

		if (animeTimer_ > maxAnimeTime_)
		{
			isEnd_ = true;
		}
	}
}

void FadeAnimation::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLACK, Vector2::Zero, fadeRate_);
}

bool FadeAnimation::isChangeScene()
{
	// ��x true �Ŏ擾�����������x�擾���Ȃ��悤�ɂ���i���}�I�j
	if (isChangeScene_)
	{
		isChangeScene_ = false;

		return true;
	}

	return false;
}
