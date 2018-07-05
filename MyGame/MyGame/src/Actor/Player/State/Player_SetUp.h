#pragma once
#include"PlayerState.h"

class Player_SetUp :public PlayerState {
public:
	Player_SetUp(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};