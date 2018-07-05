#pragma once

#include "KousatenBulding.h"
#include "../../../../Graphic/Model.h"

#include "../../../../Actor/EventActor/Manhoru/Manhoru.h"
#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"

KousatenBulding::KousatenBulding(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "KousatenBulding", position, 3, 2, rotationNum) {
	eventType_ = EventType::EVENT_JUNCTION;
}

KousatenBulding::KousatenBulding(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "KousatenBulding", position, 3, 2, rotationNum) {
	eventType_ = EventType::EVENT_JUNCTION;
}

KousatenBulding::KousatenBulding(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "KousatenBulding", width, height, 3, 2, rotationNum, offset) {
	eventType_ = EventType::EVENT_JUNCTION;
}

void KousatenBulding::update(float deltaTime){

}

void KousatenBulding::draw() const {

}

void KousatenBulding::end() {
}

std::shared_ptr<BuildingBase> KousatenBulding::clone() {
	return std::make_shared<KousatenBulding>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> KousatenBulding::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<KousatenBulding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> KousatenBulding::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<KousatenBulding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> KousatenBulding::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<KousatenBulding>(world, width, height, rotationNum, offset);
}
