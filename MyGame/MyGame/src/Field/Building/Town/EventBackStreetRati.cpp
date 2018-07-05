#include "EventBackStreetRati.h"
#include "../../../Graphic/Model.h"

EventBackStreetRati::EventBackStreetRati(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset):
	BuildingBase(world, "EventBackStreetRati", width, height, 1, 1, rotationNum, offset) {
	eventType_ = EventType::EVENT_BACKSTREET_RATI;
}

void EventBackStreetRati::update(float deltaTime)
{
}

void EventBackStreetRati::draw() const
{
}

void EventBackStreetRati::end()
{
}

std::shared_ptr<BuildingBase> EventBackStreetRati::clone(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset)
{
	return std::make_shared<EventBackStreetRati>(world, width, height, rotationNum, offset);
}
