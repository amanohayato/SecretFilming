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
	// ���݂̎��Ԃ̍X�V
	time_ += deltaTime;

	// ���݂̎��Ԃ��I�����ԂɂȂ��Ă��Ȃ�������
	if (time_ < limitTime_)
	{
		// ���b���̒l�̕␳
		curScale_ += (scaleChangeWidth_ * deltaTime);
		return;
	}

	// �l�̕␳
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
