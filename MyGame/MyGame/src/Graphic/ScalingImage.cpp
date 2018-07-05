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
	// ���݂̎��Ԃ̍X�V
	time_ += deltaTime;

	// ���݂̎��Ԃ��I�����ԂɂȂ��Ă��Ȃ�������
	if (time_ < limitTime_)
	{
		// ���b���̒l�̕␳
		curScale_ += (scaleChangeWidth_ * deltaTime);
		curAlpha_ += (alphaChangeWidth_ * deltaTime);
		return;
	}

	// �l�̕␳
	curScale_ = afterScale_;
	curAlpha_ = afterAlpha_;
}

void ScalingImage::draw()
{
	// �X�v���C�g�̕\��
	Sprite::GetInstance().Draw(id_, position_, origin_, curAlpha_, curScale_);
}

bool ScalingImage::isAnimationEnd()
{
	return (time_ >= limitTime_);
}
