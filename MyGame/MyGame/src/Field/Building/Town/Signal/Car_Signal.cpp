#include "Car_Signal.h"
#include "../../../../Graphic/Model.h"
#include "../../../../Scene/Manager/GameDataManager.h"
#include"../../../../Input/Keyboard.h"

Car_Signal::Car_Signal(IWorld * world, const Vector3 & position, int rotationNum) :
	BuildingBase(world, "Car_Signal", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_GREEN));
}

Car_Signal::Car_Signal(IWorld * world, const Vector2 & position, int rotationNum) :
	BuildingBase(world, "Car_Signal", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_GREEN));
}

static constexpr float signalsize = 0.4f;
Car_Signal::Car_Signal(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset) :
	BuildingBase(world, "Car_Signal", width, height, signalsize, signalsize, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_GREEN));
	float angle = (float)rotationNum * 90.f;
	auto off = (Matrix::CreateTranslation(Vector3{ -6.0f,0.0f,0.0f })*Matrix::CreateRotationY(angle)).Translation();

	
	position_ = Vector3((width * (float)SQUARES_WIDTH) + ((1.0f * (float)SQUARES_WIDTH) / 2) + off.x, 0, (height * (float)SQUARES_HEIGHT) - ((1.0f * (float)SQUARES_HEIGHT) / 2) + off.z + 2);
	collision_ = BuildingCollision(position_, Vector3((-(signalsize / 2) * (float)SQUARES_WIDTH) , 0, (-(signalsize / 2) * (float)SQUARES_HEIGHT) ), Vector3(((signalsize / 2) * (float)SQUARES_WIDTH) , 0, ((signalsize / 2) * (float)SQUARES_HEIGHT)+2 ));
}

void Car_Signal::update(float deltaTime)
{
	int signal_type = GameDataManager::getInstance().getCarSignalNum();
	switch (signal_type)
	{
	case Signal_Red:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_RED));
		break;
	case Signal_Yellow:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_YELLOW));
		break;
	case Signal_Green:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_ROADWAY_GREEN));
		break;
	}
}

void Car_Signal::draw() const
{
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_ + rotation_.Right()*9.8f + rotation_.Forward()*1.8f);
	animation_.Draw(pose);
}

void Car_Signal::end()
{
}

std::shared_ptr<BuildingBase> Car_Signal::clone() {
	return std::make_shared<Car_Signal>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> Car_Signal::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<Car_Signal>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Car_Signal::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<Car_Signal>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Car_Signal::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<Car_Signal>(world, width, height, rotationNum, offset);
}