#include "BuildingManager.h"
#include "BuildingBase.h"

BuildingManager::BuildingManager() {
	collisionMap_ = std::make_shared<BuildingCollisionMap>();
	initialize();
}

void BuildingManager::initialize() {
	buildings_.clear();
	collisionMap_->clear();
}

void BuildingManager::update(float deltaTime) {
	for (auto& b : buildings_) {
		b->update(deltaTime);
	}
}

void BuildingManager::draw() const {
	for (auto& b : buildings_) {
		b->draw();
	}
}

void BuildingManager::remove() {
	buildings_.remove_if([](const BuildingPtr& building) { return building->isDead(); });
	collisionMap_->remove_expired();
}

void BuildingManager::add(const BuildingPtr& building) {
	buildings_.push_front(building);
}

void BuildingManager::clone(int buildingNum, IWorld* world, const Vector3& position, int rotationNum) {
	add(std::make_shared<BuildingBase>());
}

unsigned int BuildingManager::count() const {
	return (unsigned int)buildings_.size();
}

std::list<BuildingPtr>& BuildingManager::get() {
	return buildings_;
}

std::weak_ptr<BuildingCollisionMap> BuildingManager::getCollMap() const
{
	return collisionMap_;
}

void BuildingManager::collide() {
	
}

void BuildingManager::clear() {
	buildings_.clear();
}

bool BuildingManager::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	return collisionMap_->hitToLine(firstPos, secondPos);
}
