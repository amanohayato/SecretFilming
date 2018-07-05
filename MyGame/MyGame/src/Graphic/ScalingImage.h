#pragma once

#include"DxLib.h"
#include"Sprite.h"
#include"../ID/EnumIDs.h"

// �摜�̑傫���ύX�A�j���[�V�����N���X
class ScalingImage
{
public:
	// �R���X�g���N�^
	ScalingImage(SPRITE_ID id, Vector2 position, Vector2 origin, Vector2 beforeScale, Vector2 afterScale, float beforeAlpha, float afterAlpha, float scalingTime);

	// 
	void reSet(Vector2 afterScale, float afterAlpha, float scalingTime);

	// �X�V
	void update(float deltaTime);

	// �`��
	void draw();

	// �A�j���[�V�������I����Ă��邩�̔���
	bool isAnimationEnd();

private:

	// �\������X�v���C�g��ID
	SPRITE_ID id_;

	// �\������X�v���C�g�̈ʒu
	Vector2 position_;

	// �\������X�v���C�g�̒��S�_
	Vector2 origin_;

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

	// ���݂̃X�v���C�g�̔Z��
	float curAlpha_;

	// �ω���̃X�v���C�g�̔Z��
	float afterAlpha_;

	// ���b������̃X�v���C�g�̔Z���̕ω���
	float alphaChangeWidth_;
};