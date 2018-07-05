#include "ScalingSprite.h"

ScalingSprite::ScalingSprite(Vector2 beforeScale, Vector2 afterScale, float scalingTime)
{
	limitTime_ = scalingTime;

	curScale_ = beforeScale;
	afterScale_ = afterScale;
	scaleChangeWidth_ = (afterScale - curScale_) / scalingTime;
}

void ScalingSprite::reSet(Vector2 afterScale, float scalingTime)
{
	limitTime_ = scalingTime;

	afterScale_ = afterScale;
	scaleChangeWidth_ = (afterScale - curScale_) / scalingTime;
}

void ScalingSprite::update(float deltaTime)
{
	// 現在の時間の更新
	time_ += deltaTime;

	// 現在の時間が終了時間になっていなかったら
	if (time_ < limitTime_)
	{
		// 毎秒毎の値の補正
		curScale_ += (scaleChangeWidth_ * deltaTime);
		return;
	}

	// 値の補正
	curScale_ = afterScale_;
}

Vector2 ScalingSprite::getCurScale()
{
	return curScale_;
}

bool ScalingSprite::isAnimationEnd()
{
	return (time_ >= limitTime_);
}
