#include "TutorialEnd.h"

TutorialEnd::TutorialEnd()
{
}

void TutorialEnd::onStart()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);




	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);


}

void TutorialEnd::onUpdate(float deltaTime)
{
	displayA_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	displayA_Push_ = true;

	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
	{
		// ÉZÉåÉNÉgSEÇçƒê∂
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		isCommandEnd_ = true;
	}
}

void TutorialEnd::onDraw() const
{
}

void TutorialEnd::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);




	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);


}

void TutorialEnd::setText()
{
	textBox_.add("TutorialText/23_TutorialEnd/TutorialEnd.txt");
}
