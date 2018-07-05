#include "ReturnViewPoint.h"

ReturnViewPoint::ReturnViewPoint(std::shared_ptr<Player> player)
{
	player_ = player;
}

void ReturnViewPoint::onStart()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);




	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);

}

void ReturnViewPoint::onUpdate(float deltaTime)
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

void ReturnViewPoint::onDraw() const
{
}

void ReturnViewPoint::onEnd()
{
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);




	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);

}

void ReturnViewPoint::setText()
{
	textBox_.add("TutorialText/12_ReturnViewPoint/ReturnViewPoint.txt");
}
