#include "Apartment_2.h"
#include "../../../Graphic/Model.h"

Apartment_2::Apartment_2(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "Apartment_2", position, 12, 7, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_2));
}

Apartment_2::Apartment_2(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "Apartment_2", position, 12, 7, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_2));
}

Apartment_2::Apartment_2(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "Apartment_2", width, height, 12, 7, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_APARTMENT_2));
}

void Apartment_2::update(float deltaTime) {

}

void Apartment_2::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void Apartment_2::end() {
}

std::shared_ptr<BuildingBase> Apartment_2::clone() {
	return std::make_shared<Apartment_2>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> Apartment_2::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<Apartment_2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Apartment_2::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<Apartment_2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Apartment_2::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<Apartment_2>(world, width, height, rotationNum, offset);
}
