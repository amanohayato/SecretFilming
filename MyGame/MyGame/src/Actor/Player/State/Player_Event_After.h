#pragma once
#include"PlayerState.h"

class Player_Event_After : public PlayerState {
public:
	Player_Event_After(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
private:
	float timer_{ 0.0f };
};
