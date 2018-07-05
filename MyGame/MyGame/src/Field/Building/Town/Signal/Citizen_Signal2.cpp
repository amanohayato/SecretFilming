#include "Citizen_Signal2.h"
#include "../../../../Graphic/Model.h"
#include "../../../../Scene/Manager/GameDataManager.h"

Citizen_Signal2::Citizen_Signal2(IWorld * world, const Vector3 & position, int rotationNum) :
	BuildingBase(world, "Citizen_Signal2", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN));
}

Citizen_Signal2::Citizen_Signal2(IWorld * world, const Vector2 & position, int rotationNum) :
	BuildingBase(world, "Citizen_Signal2", position, 1, 1, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN));
}

static constexpr float signalsize = 0.2f;
Citizen_Signal2::Citizen_Signal2(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset) :
	BuildingBase(world, "Citizen_Signal2", width, height, signalsize, signalsize, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN));
	float angle = (float)rotationNum * 90.f;
	auto off = (Matrix::CreateTranslation(Vector3{ 0.0f,0.0f,6.0f })*Matrix::CreateRotationY(angle)).Translation();
	position_ = Vector3((width * (float)SQUARES_WIDTH) + ((1.0f * (float)SQUARES_WIDTH) / 2) + off.x, 0, (height * (float)SQUARES_HEIGHT) - ((1.0f * (float)SQUARES_HEIGHT) / 2) + off.z - 2);
	collision_ = BuildingCollision(position_, Vector3((-(signalsize / 2) * (float)SQUARES_WIDTH), 0, (-(signalsize / 2) * (float)SQUARES_HEIGHT)), Vector3(((signalsize / 2) * (float)SQUARES_WIDTH), 0, ((signalsize / 2) * (float)SQUARES_HEIGHT) - 2));
}

void Citizen_Signal2::update(float delta_time)
{
	int signal_type = GameDataManager::getInstance().getCitizenSignalNum();
	switch (signal_type)
	{
	case Signal_Red:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_RED));
		break;
	case Signal_Yellow:
		//animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_NONE));
		ci_yellow_signal(delta_time);
		break;
	case Signal_Green:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN));
		break;
	}

}

void Citizen_Signal2::draw() const
{
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_ + rotation_.Right()*3.2f + rotation_.Forward()*0.4f);
	animation_.Draw(pose);
}

void Citizen_Signal2::end()
{
}

void Citizen_Signal2::ci_yellow_signal(float delta_time)
{
	count += delta_time;
	if (count <= 0.5f)
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN));
	else if (count > 1.0f)
		count = 0;
	else
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SIGNAL_SIDEWALK_NONE));
}

std::shared_ptr<BuildingBase> Citizen_Signal2::clone() {
	return std::make_shared<Citizen_Signal2>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> Citizen_Signal2::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<Citizen_Signal2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Citizen_Signal2::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<Citizen_Signal2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> Citizen_Signal2::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<Citizen_Signal2>(world, width, height, rotationNum, offset);
}