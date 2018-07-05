#pragma once
#include"PlayerState.h"

class Player_Fall : public PlayerState {
public:
	Player_Fall(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};