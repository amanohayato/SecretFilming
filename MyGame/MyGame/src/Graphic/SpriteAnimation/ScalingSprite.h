#pragma once

#include<DxLib.h>
#include "../../math/Vector2.h"

// �摜�̑傫���ύX�A�j���[�V�����N���X
class ScalingSprite
{
public:
	// �R���X�g���N�^
	ScalingSprite(Vector2 beforeScale, Vector2 afterScale, float scalingTime);

	// �l���Đݒ�
	void reSet(Vector2 afterScale, float scalingTime);

	// �X�V
	void update(float deltaTime);

	// ���݂̃X�P�[�����擾
	Vector2 getCurScale();

	// �A�j���[�V�������I����Ă��邩�̔���
	bool isAnimationEnd();

private:

	// �o�ߎ���
	float time_{ 0.0f };

	// �I�����鎞��
	float limitTime_{ 0.0f };

	// ���݂̃X�P�[��
	Vector2 curScale_;

	// �ω���̃X�P�[��
	Vector2 afterScale_;

	// ���b������̃X�P�[���̕ω���
	Vector2 scaleChangeWidth_;
};