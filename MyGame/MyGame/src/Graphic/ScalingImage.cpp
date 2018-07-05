#include "ScalingImage.h"
#include "../Camera/CaptureScreen.h"

ScalingImage::ScalingImage(SPRITE_ID id, Vector2 position, Vector2 origin, Vector2 beforeScale, Vector2 afterScale, float beforeAlpha, float afterAlpha, float scalingTime)
{
	id_ = id;
	position_ = position;
	origin_ = origin;
	limitTime_ = scalingTime;

	curScale_ = beforeScale;
	afterScale_ = afterScale;
	scaleChangeWidth_ = (afterScale - curScale_) / scalingTime;

	curAlpha_ = beforeAlpha;
	afterAlpha_ = afterAlpha;
	alphaChangeWidth_ = (afterAlpha - curAlpha_) / scalingTime;
}

void ScalingImage::reSet(Vector2 afterScale, float afterAlpha, float scalingTime)
{
	limitTime_ = scalingTime;

	afterScale_ = afterScale;
	scaleChangeWidth_ = (afterScale - curScale_) / scalingTime;

	afterAlpha_ = afterAlpha;
	alphaChangeWidth_ = (afterAlpha - curAlpha_) / scalingTime;
}

void ScalingImage::update(float deltaTime)
{
	// 現在の時間の更新
	time_ += deltaTime;

	// 現在の時間が終了時間になっていなかったら
	if (time_ < limitTime_)
	{
		// 毎秒毎の値の補正
		curScale_ += (scaleChangeWidth_ * deltaTime);
		curAlpha_ += (alphaChangeWidth_ * deltaTime);
		return;
	}

	// 値の補正
	curScale_ = afterScale_;
	curAlpha_ = afterAlpha_;
}

void ScalingImage::draw()
{
	// スプライトの表示
	Sprite::GetInstance().Draw(id_, position_, origin_, curAlpha_, curScale_);
}

bool ScalingImage::isAnimationEnd()
{
	return (time_ >= limitTime_);
}
