#pragma once

#include"../../SubScene.h"
#include "../../../../Graphic/SpriteAnimation/ScalingSprite.h"

#include <vector>
#include <memory>

class DisplayPhoto : public SubScene {
public:
	DisplayPhoto();

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

	void stampStart();

	bool isEndAnimation();

private:

	// �ʐ^���~���Ă��鉉�o�p�N���X
	std::vector<std::shared_ptr<ScalingSprite>> photoAnims_;

	// �~���Ă���ʐ^�̃t���[���̉��o�p�N���X
	//std::shared_ptr<ScalingSprite> photoFrameAnims_;
	
	// ����ڂ̎ʐ^�̕\���A�j���[�V������\�����Ă��邩
	int displayPhotoCount_{ 0 };

	// �����̎ʐ^��\�����邩�H
	int photoNumber_{ 6 };

	// �ő剽���̎ʐ^��\�����邩�H
	static const int maxPhotoNumber_{ 6 };

	// �X�^���v���������A�j���[�V�������J�n���ꂽ���̃t���O
	bool isStampStart_;

	// �X�^���v���������A�j���[�V�������܂�Ԃ��ꂽ���̃t���O
	bool isAnimReturn_;
};