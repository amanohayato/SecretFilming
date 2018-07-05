#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class ShootingSuccess : public TutorialCommand
{
public:
	ShootingSuccess(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;
	std::shared_ptr<TutorialEnemy> enemy_;

	bool finalChangeAlpa_{ false };

	// UI�����\���摜�̔Z��
	float blindAlpa_{ 0.0f };

	// �ω����UI�����\���摜�̔Z��
	float afterBlindAlpa_{ 0.0f };

	// ���t���[�����Ƃ�UI�����\���̔Z���̕ύX
	float blindAlpaChangeRate_{ 0.0f };
};