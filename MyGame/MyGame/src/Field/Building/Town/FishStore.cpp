#include "FishStore.h"
#include "../../../Graphic/Model.h"
#include"../../../Actor/Body/BoundingSphere.h"

FishStore::FishStore(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "FishStore", position, 5, 5, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_FISH));
}

FishStore::FishStore(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "FishStore", position, 5, 5, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_FISH));
}

FishStore::FishStore(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "FishStore", width, height, 5, 5, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_FISH));
	Vector3 position = rotation_.Forward().Normalize() * 50.0f + Vector3::Up * 5.0f;
	body_ = std::make_shared<BoundingSphere>(position, 25.0f);
	status_.setPosition(position_ + (rotation_.Forward().Normalize() * 50.0f));
	Matrix rot = Matrix::CreateRotationY(-90.0f * rotationNum_);
	status_.setRotation(-rot);
}

void FishStore::update(float deltaTime) {
	constexpr float ZERO = 0.f;
	MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(ZERO, ZERO, ZERO, ZERO));
	emission_();
	emission_ = [] {};
	collide();
}

void FishStore::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	body_->transform(pose)->draw();
	animation_.Draw(pose);
}

void FishStore::end() {
}

void FishStore::fish_store() {

}

void FishStore::message(EventMessage eventMessage, void * param)
{
	if (eventMessage == EventMessage::Emission) {
		emission_ = [&] {
			constexpr float power = 0.4f;
			MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(power, power, power, power));
		};
	}
}

void FishStore::onCollide(Actor & other)
{
	other.receiveMessage(EventMessage::Hide_InCamera, (void*)this);
}

std::shared_ptr<BuildingBase> FishStore::clone() {
	return std::make_shared<FishStore>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> FishStore::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<FishStore>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> FishStore::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<FishStore>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> FishStore::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<FishStore>(world, width, height, rotationNum, offset);
}
