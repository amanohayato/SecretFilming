#include "PoliceBox.h"
#include "../../../Graphic/Model.h"

#include "../../../Actor/EventActor/Police/Police.h"

PoliceBox::PoliceBox(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "PoliceBox", position, 3, 4, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_KOUBAN));
}

PoliceBox::PoliceBox(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "PoliceBox", position, 3, 4, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_KOUBAN));
}

PoliceBox::PoliceBox(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "PoliceBox", width, height, 3, 4, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_KOUBAN));
	eventType_ = EventType::EVENT_POLICE;

	Matrix rotateMat = Matrix::Identity;
	rotateMat *= Matrix::CreateRotationY(float(rotationNum * 90.0f));



	Matrix mat = Matrix::Identity;
	mat =
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(float(rotationNum * 90.0f)+1)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(position_+rotateMat.Forward()*30.0f);

	auto police = std::make_shared<Police>(world, mat);
	world_->addActor(ActorGroup::EVENT_ACTOR, police);
	mPolice = police;
}

void PoliceBox::update(float deltaTime) {

}

void PoliceBox::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void PoliceBox::end() {
}

std::shared_ptr<BuildingBase> PoliceBox::clone() {
	return std::make_shared<PoliceBox>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> PoliceBox::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<PoliceBox>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> PoliceBox::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<PoliceBox>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> PoliceBox::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<PoliceBox>(world, width, height, rotationNum, offset);
}

ActorPtr PoliceBox::GetPolice()
{
	return mPolice;
}
