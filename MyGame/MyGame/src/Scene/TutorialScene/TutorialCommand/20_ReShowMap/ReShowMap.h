#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"

class ReShowMap : public TutorialCommand
{
public:
	ReShowMap(std::shared_ptr<Player> player);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;

	// �v���C���[���͂�҂��Ă��邩�̃t���O
	bool isWaitInput_{ false };

	bool finalChangeAlpa_{ false };

	// UI�����\���摜�̔Z��
	float blindAlpa_{ 0.0f };

	// �ω����UI�����\���摜�̔Z��
	float afterBlindAlpa_{ 0.0f };

	// ���t���[�����Ƃ�UI�����\���̔Z���̕ύX
	float blindAlpaChangeRate_{ 0.0f };
};