#pragma once
#include "../TutorialCommand.h"
#include "../../../../Actor/Enemy/TutorialEnemy/TutorialEnemy.h"

class TutorialStart : public TutorialCommand
{
public:
	TutorialStart(std::shared_ptr<TutorialEnemy> enemy);

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

	std::shared_ptr<TutorialEnemy> enemy_;
};