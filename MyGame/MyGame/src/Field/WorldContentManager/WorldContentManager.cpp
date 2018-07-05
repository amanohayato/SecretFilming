 #include "WorldContentManager.h"
#include "../../World/IWorld.h"
#include "../Building/BuildingManager.h"
#include "../../World/ObjectManager.h"
#include "../Building/Buildings.h"
#include "../../Graphic/Model.h"
#include "../Map/MapGenerator.h"


WorldContentManager::WorldContentManager():
	skybox_(nullptr), field_(nullptr)
{
	objManager_ = std::make_shared<ObjectManager>();
}

void WorldContentManager::initialize()
{
	objManager_->initialize();
	
	mapGenerator_ = std::make_shared<MapGenerator>(&objManager_->getBuildings());

}

void WorldContentManager::setupWorld(IWorld* world)
{
	world_ = world;

	field_ = std::make_shared<Field>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_STAGE));
	skybox_ = std::make_shared<Skybox>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_SKYBOX));
	addBuilding();
}

void WorldContentManager::update(float deltaTime)
{
	if (field_ != nullptr) field_->update(deltaTime);
	if (skybox_ != nullptr) skybox_->update(deltaTime);

	objManager_->update(deltaTime);
}

void WorldContentManager::drawSkyBox() const
{
	if (skybox_ != nullptr) skybox_->draw();
	if (field_ != nullptr) field_->draw();
}

void WorldContentManager::draw() const
{
	if (skybox_ != nullptr) skybox_->draw();
	if (field_ != nullptr) field_->draw();
	mapGenerator_->draw();
	objManager_->draw();
}

void WorldContentManager::actorDraw() const
{
	objManager_->actorDraw();
}

void WorldContentManager::buildingDraw() const
{
	if (field_ != nullptr) field_->shadowDraw();
	mapGenerator_->draw();
	objManager_->buildingDraw();
}

void WorldContentManager::shadowDraw() const
{
	//if (field_ != nullptr) field_->draw();
	mapGenerator_->draw();
	objManager_->shadowDraw();

}

std::shared_ptr<Field> WorldContentManager::getField()
{
	return field_;
}

std::shared_ptr<Skybox> WorldContentManager::getSkybox()
{
	return skybox_;
}

void WorldContentManager::addActor(ActorGroup group, const ActorPtr& actor)
{
	objManager_->addActor(group, actor);
}

void WorldContentManager::addBuilding()
{
	mapGenerator_->setUpList(world_);
	mapGenerator_->read("res/Data/protomap.csv","res/Data/slicemap.csv");
	mapGenerator_->generate();

	//objManager_->addBuilding(new_building<House_1>(world_,Vector3{ 150.0f, 0.0f, 0.0f }, 0));
	//objManager_->addBuilding(new_building<SmokingArea>(world_, Vector3{ -150.0f, 0.0f, 0.0f }, 0));
	//objManager_->addBuilding(new_building<Apartment_1>(world_, 4, 0, 0));
}

ActorPtr WorldContentManager::findActor(const std::string & name)
{
	return objManager_->findActor(name);
}

void WorldContentManager::findActor(ActorGroup group, const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	objManager_->findActor(group, name, actorList);
}

void WorldContentManager::handleMessage(EventMessage message, void * param)
{
	objManager_->handleMessage(message, param);
}

unsigned int WorldContentManager::getSize(ActorGroup group) const
{
	return objManager_->getSize(group);
}

bool WorldContentManager::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	return objManager_->hitToLine(firstPos, secondPos);
}

std::weak_ptr<ObjectManager> WorldContentManager::getObjManager()
{
	return objManager_;
}


