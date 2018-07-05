#include "TrafficLight_Human.h"
#include "../../../Graphic/Model.h"

TrafficLight_Human::TrafficLight_Human(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "TrafficLight_Human", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_HUMAN));
}

TrafficLight_Human::TrafficLight_Human(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "TrafficLight_Human", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_HUMAN));
}

TrafficLight_Human::TrafficLight_Human(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "TrafficLight_Human", width, height, 1, 1, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_HUMAN));
}

void TrafficLight_Human::update(float deltaTime) {

}

void TrafficLight_Human::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void TrafficLight_Human::end() {
}

void TrafficLight_Human::onCollide(Actor& other) {
}

void TrafficLight_Human::onEvent() {

}

std::shared_ptr<BuildingBase> TrafficLight_Human::clone() {
	return std::make_shared<TrafficLight_Human>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> TrafficLight_Human::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<TrafficLight_Human>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TrafficLight_Human::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<TrafficLight_Human>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TrafficLight_Human::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<TrafficLight_Human>(world, width, height, rotationNum, offset);
}
