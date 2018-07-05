#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	initialize();
}

void ObjectManager::initialize()
{
	actors_.initialize();
	buildings_.initialize();
}

void ObjectManager::update(float deltaTime)
{
	actors_.update(deltaTime);
	buildings_.update(deltaTime);
	collide();
	remove();
}

void ObjectManager::draw() const
{
	buildings_.draw();
	actors_.draw();
}

void ObjectManager::buildingDraw() const
{
	buildings_.draw();
}

void ObjectManager::actorDraw() const
{
	actors_.draw();
}

void ObjectManager::shadowDraw() const
{
	buildings_.draw();
	actors_.shadowDraw();
}

void ObjectManager::remove()
{
	actors_.remove();
	buildings_.remove();
}

void ObjectManager::addActor(ActorGroup group, const ActorPtr & actor)
{
	actors_.addActor(group, actor);
}

void ObjectManager::addBuilding(const BuildingPtr & building)
{
	buildings_.add(building);
}

void ObjectManager::collide(){
	actors_.collide();
	constexpr int range = 2;
	//‚±‚±‚ÅŒš•¨‚Æ‚Ì“–‚½‚è”»’è‚ð‚â‚Á‚Ä‚¢‚é
	auto player = getActors().get()[ActorGroup::PLAYER_ACTOR]->getChildren();
	auto enemy = getActors().get()[ActorGroup::ENEMY_ACTOR]->getChildren();
	auto citizen = getActors().get()[ActorGroup::CITIZEN_ACTOR]->getChildren();
	for (auto c : player) {
		//auto s = buildings_.getCollMap().lock()->getBuildingLists(c->GetPosition(), range);
		for (auto& b : buildings_.getCollMap().lock()->getBuildingLists(c->getPosition(), range)) {
			if (b.lock()->hitCheck(c->getPosition())) {
				b.lock()->onCollide(*c.get());
			}
		}
	}
	for (auto c : citizen) {
		for (auto& b : buildings_.getCollMap().lock()->getBuildingLists(c->getPosition(), range)) {
			if (b.lock()->hitCheck(c->getPosition())) {
				b.lock()->onCollide(*c.get());
				c->receiveMessage(EventMessage::Hit_Object);
			}
		}
	}
	/*
	for (auto c : enemy) {
		for (auto& b : buildings_.getCollMap().lock()->getBuildingLists(c->getPosition(), range)) {
			if (b.lock()->hitCheck(c->getPosition())) {

			}
		}
	}*/
}

ActorPtr ObjectManager::findActor(const std::string & name)
{
	return actors_.findActor(name);
}

void ObjectManager::findActor(ActorGroup group, const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	return actors_.findActor(group, name, actorList);
}

void ObjectManager::handleMessage(EventMessage message, void * param)
{
	actors_.handleMessage(message, param);
}

unsigned int ObjectManager::getSize(ActorGroup group) const
{
	return actors_.getSize(group);
}

bool ObjectManager::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	return buildings_.hitToLine(firstPos, secondPos);
}

ActorManager & ObjectManager::getActors()
{
	return actors_;
}

BuildingManager & ObjectManager::getBuildings()
{
	return buildings_;
}
