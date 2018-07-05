#include "TrafficLight_Car.h"
#include "../../../Graphic/Model.h"

TrafficLight_Car::TrafficLight_Car(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "TrafficLight_Car", position, 1, 1, rotationNum){
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_CAR));
}

TrafficLight_Car::TrafficLight_Car(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "TrafficLight_Car", position, 1, 1, rotationNum){
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_CAR));
}

TrafficLight_Car::TrafficLight_Car(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "TrafficLight_Car", width, height, 1, 1, rotationNum, offset){
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SHINGOU_CAR));
}

void TrafficLight_Car::update(float deltaTime) {

}

void TrafficLight_Car::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void TrafficLight_Car::end() {
}

std::shared_ptr<BuildingBase> TrafficLight_Car::clone() {
	return std::make_shared<TrafficLight_Car>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> TrafficLight_Car::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<TrafficLight_Car>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TrafficLight_Car::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<TrafficLight_Car>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TrafficLight_Car::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<TrafficLight_Car>(world, width, height, rotationNum, offset);
}
