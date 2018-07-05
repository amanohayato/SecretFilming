#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class StartHide : public TutorialCommand
{
public:
	StartHide(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;

	std::shared_ptr<TutorialEnemy> enemy_;

	// �`���[�g���A���p�̉F���l�̌x���x
	float tutorialAwareness_;

	// �v���C���[���͂�҂��Ă��邩�̃t���O
	bool isWaitInput_{ false };
};