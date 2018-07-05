#pragma once
#include "../TutorialCommand.h"

class LookSpecifiedPointIcon : public TutorialCommand
{
public:
	LookSpecifiedPointIcon();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	bool finalChangeAlpa_{ false };

	// UI�����\���摜�̔Z��
	float blindAlpa_{ 0.0f };

	// �ω����UI�����\���摜�̔Z��
	float afterBlindAlpa_{ 0.0f };

	// ���t���[�����Ƃ�UI�����\���̔Z���̕ύX
	float blindAlpaChangeRate_{ 0.0f };
};