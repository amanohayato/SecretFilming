#ifndef POLICE_BOX_H_
#define POLICE_BOX_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"

class PoliceBox : public BuildingBase {
public:
	PoliceBox(IWorld* world, const Vector3& position, int rotationNum = 0);
	PoliceBox(IWorld* world, const Vector2& position, int rotationNum = 0);
	PoliceBox(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

public:
	//ポリスアクターを取得
	ActorPtr GetPolice();

private:
	ActorPtr mPolice;
};

#endif // !POLICE_BOX_H_