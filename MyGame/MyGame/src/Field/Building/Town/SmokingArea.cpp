#include "SmokingArea.h"
#include "../../../Graphic/Model.h"

SmokingArea::SmokingArea(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "SmokingArea", position, 3, 2, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SMOKING_AREA));
}

SmokingArea::SmokingArea(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "SmokingArea", position, 3, 2, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SMOKING_AREA));
}

SmokingArea::SmokingArea(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "SmokingArea", width, height, 3, 2, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SMOKING_AREA));
	eventType_ = EventType::EVENT_SMOKING;

}

void SmokingArea::update(float deltaTime) {

}

void SmokingArea::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void SmokingArea::end() {
}

void SmokingArea::playSmoke()
{
	if (!_se.expired())return;
	auto FrameIndex = MV1SearchFrame(animation_.getModelHandle(), "mob_modele11:mixamorig:RightHandRing3");
	Matrix FrameMatrix = DXConverter::GetInstance().ToMatrix(MV1GetFrameLocalWorldMatrix(animation_.getModelHandle(), FrameIndex));
	auto effect = std::make_shared<SmokeEffect>(FrameMatrix.Translation() + FrameMatrix.Forward()*5.0f);
	_se = effect;
	world_->addActor(ActorGroup::UI_ACTOR,effect);
}

void SmokingArea::smoking() {

}

void SmokingArea::message(EventMessage eventMessage, void * param)
{
	if (eventMessage == EventMessage::Play_Smoke) {
		playSmoke();
	}
}

std::shared_ptr<BuildingBase> SmokingArea::clone() {
	return std::make_shared<SmokingArea>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> SmokingArea::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<SmokingArea>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> SmokingArea::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<SmokingArea>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> SmokingArea::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<SmokingArea>(world, width, height, rotationNum, offset);
}
