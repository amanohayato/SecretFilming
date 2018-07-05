#include "NullRandomEvent.h"

NullRandomEvent::NullRandomEvent(IWorld & world){}

void NullRandomEvent::Initialize(){}

void NullRandomEvent::Update(){}

void NullRandomEvent::Draw() const{}

bool NullRandomEvent::IsEnd() const
{
	return false;
}

void NullRandomEvent::End(){}

RandomEvent NullRandomEvent::Next() const
{
	return RandomEvent();
}
