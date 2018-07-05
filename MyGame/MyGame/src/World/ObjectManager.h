#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include "../Actor/ActorManager.h"
#include "../Field/Building/BuildingManager.h"

class ObjectManager {
public:
	ObjectManager();
	void initialize();
	void update(float deltaTime);
	void draw() const;
	void buildingDraw() const;
	void actorDraw() const;
	void shadowDraw() const;
	void remove();
	void addActor(ActorGroup group, const ActorPtr& actor);
	void addBuilding(const BuildingPtr& building);
	void collide();

	ActorPtr findActor(const std::string& name);
	// 引数のリストに見つけたアクターを追加する
	void findActor(ActorGroup group, const std::string& name, std::list<std::weak_ptr<Actor>>& actorList);
	void handleMessage(EventMessage message, void* param);
	unsigned int getSize(ActorGroup group) const;

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);

	ActorManager& getActors();
	BuildingManager& getBuildings();

private:
	ActorManager actors_{};
	BuildingManager buildings_{};
};

#endif // !OBJECT_MANAGER_H_
