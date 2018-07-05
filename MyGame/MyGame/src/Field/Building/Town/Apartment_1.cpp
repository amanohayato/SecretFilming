#include "Apartment_1.h"
#include "../../../Graphic/Model.h"

Apartment_1::Apartment_1(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "Apartment_1", position, 30, 10, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_1));
}

Apartment_1::Apartment_1(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "Apartment_1", position, 30, 10, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_1));
}

Apartment_1::Apartment_1(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "Apartment_1", width, height, 30, 10, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_1));
}

void Apartment_1::update(float deltaTime) {

}

void Apartment_1::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void Apartment_1::end() {
}

std::shared_ptr<BuildingBase> Apartment_1::clone() {
	return std::make_shared<Apartment_1>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> Apartment_1::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<Apartment_1>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Apartment_1::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<Apartment_1>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Apartment_1::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<Apartment_1>(world, width, height, rotationNum, offset);
}
