#pragma once
#include"PlayerState.h"

class Player_Event_Before : public PlayerState {
public:
	Player_Event_Before(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
private:
	float amount{0.0f};
};