#pragma once
#include"PlayerState.h"
class IWorld;

class Player_EventAction : public PlayerState {
public:
	Player_EventAction(IWorld* world, ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
private:
	ActorPtr enemy_{ nullptr };
	static const int maxHeartSpeed{ 80000 };
	int minHeartSpeed;
};