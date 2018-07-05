#include "NekoBuilding.h"
#include "../../../../Actor/EventActor/AbductUfo/AbductUfo.h"
#include "../../../../Actor/EventActor/Cat/AbductCat.h"

NekoBuilding::NekoBuilding(IWorld * world, const Vector3 & position, int rotationNum):
BuildingBase(world, "NekoBuilding", position, 1, 1, rotationNum) {
}

NekoBuilding::NekoBuilding(IWorld * world, const Vector2 & position, int rotationNum):
	BuildingBase(world, "NekoBuilding", position, 1, 1, rotationNum) {
}

NekoBuilding::NekoBuilding(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset):
	BuildingBase(world, "NekoBuilding", width, height, 1, 1, rotationNum, offset) {

	eventType_ = EventType::EVENT_NEKO;

	auto cat = std::make_shared<AbductCat>(world, position_);
	world_->addActor(ActorGroup::EVENT_ACTOR, cat);
	const Vector3 startPos = position_ - Vector3{ 200.0f,0.0f,200.0f };
	auto ufo = std::make_shared<AbductUfo>(world, startPos, position_);
	world_->addActor(ActorGroup::EVENT_ACTOR, ufo);
	ufo->setTarget(cat);

}

void NekoBuilding::update(float deltaTime)
{
}

void NekoBuilding::draw() const
{
}

void NekoBuilding::end()
{
}

std::shared_ptr<BuildingBase> NekoBuilding::clone()
{
	return std::make_shared<NekoBuilding>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> NekoBuilding::clone(IWorld * world, const Vector3 & position, int rotationNum)
{
	return std::make_shared<NekoBuilding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> NekoBuilding::clone(IWorld * world, const Vector2 & position, int rotationNum)
{
	return std::make_shared<NekoBuilding>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> NekoBuilding::clone(IWorld * world, int width, int height, int rotationNum, const Vector2 & offset)
{
	return std::make_shared<NekoBuilding>(world, width, height, rotationNum, offset);
}
