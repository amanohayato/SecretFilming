#pragma once

#include"../../SubScene.h"
#include "../../../../Graphic/SpriteAnimation/ScalingSprite.h"

#include <memory>

class ScoreSheet : public SubScene {
public:

	ScoreSheet();
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

	void bonusCalculation();

	void stampStart();

protected:

	virtual void baseInit() override;

private:

	// �����N�̎��
	enum Rank
	{
		S,
		A,
		B,
		C,
		D,
	};

	// ���̃Q�[���̃����N
	Rank rank_;

	// �����N���o�͂��邩�H
	bool displayRank_{ false };

	// �m��x�̒l�i���j
	float determination_{ 0.0f };

	// �B�����ʐ^�̖���
	int photoCount_{ 0 };

	// �B�����ʐ^�̖����ł̃{�[�i�X�l
	float photoCountBonus_{ 0.0f };

	// ������ꂽ��
	int escapeCount_{ 0 };

	// ������ꂽ�񐔂ł̃{�[�i�X�l
	float escapeCountBonus_{ 0.0f };

	// �{�[�i�X���݂̒l�i���j
	float totalScore_{ 0.0f };

	// �Q�[���̃N���A�t���O
	bool isClear_{ false };

	// �X�^���v���������A�j���[�V�������J�n���ꂽ���̃t���O
	bool isAnimStart_;

	// �X�^���v���������A�j���[�V�������܂�Ԃ��ꂽ���̃t���O
	bool isAnimReturn_;

	// �X�^���v��������鉉�o�p�N���X
	std::shared_ptr<ScalingSprite> sheetAnim_;
};