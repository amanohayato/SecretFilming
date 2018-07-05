#pragma once
#include"PlayerState.h"

class Player_Idle : public PlayerState{
public:
	Player_Idle(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};
