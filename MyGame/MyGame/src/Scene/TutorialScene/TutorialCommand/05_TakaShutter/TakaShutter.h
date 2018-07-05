#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class TakaShutter : public TutorialCommand
{
public:
	TakaShutter(std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<TutorialEnemy> enemy_;

	// �F���l�ƃz���O������_�ł����邽�߂̃^�C�}�[
	float count_{ 0.0f };

	// �z���O�������g���ځI�I�I�h�\�����邽�߂̃N���X
	AnimationDx anim_;

	// �v���C���[���͂�҂��Ă��邩�̃t���O
	bool isWaitInput_{ false };
};