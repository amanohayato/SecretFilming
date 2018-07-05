#pragma once

#include "ManhoruBulding.h"
#include "../../../../Graphic/Model.h"

#include "../../../../Actor/EventActor/Manhoru/Manhoru.h"
#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include"../../../WalkGraph.h"
#include"../../../../Input/InputChecker.h"

ManhoruBulding::ManhoruBulding(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "ManhoruBulding", position, 2, 3, rotationNum) {

}

ManhoruBulding::ManhoruBulding(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "ManhoruBulding", position, 2, 3, rotationNum) {
}

ManhoruBulding::ManhoruBulding(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "ManhoruBulding", width, height, 2, 3, rotationNum, offset) {
	eventType_ = EventType::EVENT_MANHORU;


	Matrix frontMat=
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(float(rotationNum * 90.0f) + 1)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(position_);



	auto manhoru = std::make_shared<Manhoru>(world, position_);
	
	Matrix mat = Matrix::Identity;
	mat =
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(float(rotationNum * 90.0f) + 1)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(position_);


	auto car = std::make_shared<EventCar>(world, mat);
	world_->addActor(ActorGroup::EVENT_ACTOR, manhoru);
	world_->addActor(ActorGroup::EVENT_ACTOR, car);
	mManharuActor = manhoru;
	mCarActor = car;

	edge_index_ = world_->getWalkMap().clearEdge(0, position_, width_, height_);//ÉGÉbÉWÇÃçÌèú
}

void ManhoruBulding::update(float deltaTime) {
}

void ManhoruBulding::draw() const {

}

void ManhoruBulding::end() {
}

std::shared_ptr<BuildingBase> ManhoruBulding::clone() {
	return std::make_shared<ManhoruBulding>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> ManhoruBulding::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<ManhoruBulding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> ManhoruBulding::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<ManhoruBulding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> ManhoruBulding::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<ManhoruBulding>(world, width, height, rotationNum, offset);
}

ActorPtr ManhoruBulding::GetManhoruActor()
{
	return mManharuActor;
}

ActorPtr ManhoruBulding::GetCarActor()
{
	return mCarActor;
}

int ManhoruBulding::GetEdgeIndex()
{
	return edge_index_;
}
