#include "TakoyakiYatai.h"
#include "../../../Graphic/Model.h"
#include"../../../Actor/Body/BoundingSphere.h"

TakoyakiYatai::TakoyakiYatai(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "TakoyakiYatai", position, 2, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_TAKOYAKI_YATAI));
}

TakoyakiYatai::TakoyakiYatai(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "TakoyakiYatai", position, 2, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_TAKOYAKI_YATAI));
}

TakoyakiYatai::TakoyakiYatai(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "TakoyakiYatai", width, height, 2, 1, rotationNum, offset){
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_TAKOYAKI_YATAI));
	Vector3 position = rotation_.Forward().Normalize() * 19.0f + Vector3::Up * 5.0f;
	body_ = std::make_shared<BoundingSphere>(position, 16.0f);
	status_.setPosition(position_ + (rotation_.Forward().Normalize() * 19.0f));
	Matrix rot = Matrix::CreateRotationY(-90.0f * rotationNum_);
	status_.setRotation(-rot);
}

void TakoyakiYatai::update(float deltaTime) {
	constexpr float ZERO = 0.f;
	MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(ZERO, ZERO, ZERO, ZERO));
	emission_();
	emission_ = [] {};
	collide();
}

void TakoyakiYatai::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	body_->transform(getPose())->draw();
	animation_.Draw(pose);
}

void TakoyakiYatai::end() {
}

void TakoyakiYatai::takoyakiya() {

}

void TakoyakiYatai::message(EventMessage eventMessage, void * param)
{
	if (eventMessage == EventMessage::Emission) {
		emission_ = [&] {
			constexpr float power = 0.4f;
			MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(power, power, power, power));
		};
	}
}

void TakoyakiYatai::onCollide(Actor & other)
{
	other.receiveMessage(EventMessage::Hide_InCamera, (void*)this);
}

std::shared_ptr<BuildingBase> TakoyakiYatai::clone() {
	return std::make_shared<TakoyakiYatai>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> TakoyakiYatai::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<TakoyakiYatai>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TakoyakiYatai::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<TakoyakiYatai>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> TakoyakiYatai::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<TakoyakiYatai>(world, width, height, rotationNum, offset);
}
