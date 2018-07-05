#pragma once

#include "../../BuildingBase.h"
#include "../../../../Graphic/AnimationDx.h"

class ManhoruBulding : public BuildingBase {
public:
	ManhoruBulding(IWorld* world, const Vector3& position, int rotationNum = 0);
	ManhoruBulding(IWorld* world, const Vector2& position, int rotationNum = 0);
	ManhoruBulding(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

	ActorPtr GetManhoruActor();
	ActorPtr GetCarActor();

	int GetEdgeIndex();
private:
	ActorPtr mManharuActor;
	ActorPtr mCarActor;
	
	int edge_index_{ -1 };
};
