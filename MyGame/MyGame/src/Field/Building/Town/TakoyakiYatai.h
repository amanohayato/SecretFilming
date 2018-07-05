#ifndef TAKOYAKI_YATAI_H_
#define TAKOYAKI_YATAI_H_

#include "../BuildingBase.h"
#include "../../../Graphic/AnimationDx.h"

class TakoyakiYatai : public BuildingBase {
public:
	TakoyakiYatai(IWorld* world, const Vector3& position, int rotationNum = 0);
	TakoyakiYatai(IWorld* world, const Vector2& position, int rotationNum = 0);
	TakoyakiYatai(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	void update(float deltaTime) override;
	void draw() const override;
	void end() override;

	// 固有イベント
	void takoyakiya() override;
	virtual void message(EventMessage eventMessage, void* param = nullptr) override;
	virtual void onCollide(Actor& other);

	std::shared_ptr<BuildingBase> clone() override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum) override;
	std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero) override;

private:
	std::function<void()> emission_{ [] {} };
};

#endif // !TAKOYAKI_YATAI_H_