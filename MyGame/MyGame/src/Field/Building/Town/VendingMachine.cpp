#include "VendingMachine.h"
#include "../../../Graphic/Model.h"
#include"../../../Actor/Body/BoundingSphere.h"
#include"../../../Graphic/Sprite.h"

VendingMachine::VendingMachine(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "VendingMachine", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ZIHANKI));
}

VendingMachine::VendingMachine(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "VendingMachine", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ZIHANKI));
}

VendingMachine::VendingMachine(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "VendingMachine", width, height, 1, 1, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ZIHANKI));
	eventType_ = EventType::EVENT_VENDING;
	Vector3 position = rotation_.Forward().Normalize() * 16.0f + Vector3::Up * 5.0f;
	body_ = std::make_shared<BoundingSphere>(position, 16.0f);
	status_.setPosition(position_ + (rotation_.Forward().Normalize() * (SQUARES_HEIGHT / 2.0f + PLAYER_RADIUS + 1.0f)));
	Matrix rot = Matrix::CreateRotationY(-90.0f * rotationNum_);
	status_.setRotation(-rot);

	getPosition() = getPosition() + getPose().Backward()*2.0f;
}

void VendingMachine::update(float deltaTime) {
	constexpr float ZERO = 0.f;
	MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(ZERO, ZERO, ZERO, ZERO));
	emission_();
	emission_ = [] {};
	collide();
}

void VendingMachine::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	body_->transform(getPose())->draw();
	animation_.Draw(pose);
}

void VendingMachine::end() {
}

void VendingMachine::vending() {

}

void VendingMachine::message(EventMessage eventMessage, void* param)
{
	if (eventMessage == EventMessage::Emission) {
		emission_ = [&] {
			constexpr float power = 0.4f;
			MV1SetMaterialEmiColor(animation_.getModelHandle(), 0, GetColorF(power, power, power, power));
		};
	}
}

void VendingMachine::onCollide(Actor & other)
{
	other.receiveMessage(EventMessage::Hide_InCamera, (void*)this);
}

void VendingMachine::setTexture(int type)
{
	auto i = MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0);
	switch (type)
	{
	case 1: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_VENDING_BLUE), FALSE);
		break;
	}
	case 2: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_VENDING_RED), FALSE);
		break;
	}
	default:
		break;
	}
}

std::shared_ptr<BuildingBase> VendingMachine::clone() {
	return std::make_shared<VendingMachine>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> VendingMachine::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<VendingMachine>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> VendingMachine::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<VendingMachine>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> VendingMachine::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<VendingMachine>(world, width, height, rotationNum, offset);
}
