#pragma once
#include "../TutorialCommand.h"

class TutorialEnd : public TutorialCommand
{
public:
	TutorialEnd();

	virtual void onStart() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() const override;
	virtual void onEnd() override;

	virtual void setText() override;

private:

};