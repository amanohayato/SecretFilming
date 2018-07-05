#include "EventBackStreetKaiwa.h"
#include "../../../Graphic/Model.h"

EventBackStreetKaiwa::EventBackStreetKaiwa(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset) :
	BuildingBase(world, "EventBackStreetKaiwa", width, height, 1, 1, rotationNum, offset) {
	eventType_ = EventType::EVENT_BACKSTREET_KAIWA;

}

void EventBackStreetKaiwa::update(float deltaTime)
{
}

void EventBackStreetKaiwa::draw() const
{
}

void EventBackStreetKaiwa::end()
{
}

std::shared_ptr<BuildingBase> EventBackStreetKaiwa::clone(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset)
{
	return std::make_shared<EventBackStreetKaiwa>(world, width, height, rotationNum, offset);
}
