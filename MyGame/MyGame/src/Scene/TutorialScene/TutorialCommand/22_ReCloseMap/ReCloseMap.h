#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Player/Player.h"

class ReCloseMap : public TutorialCommand
{
public:
	ReCloseMap(std::shared_ptr<Player> player);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<Player> player_;

	// �v���C���[���͂�҂��Ă��邩�̃t���O
	bool isWaitInput_{ false };
};