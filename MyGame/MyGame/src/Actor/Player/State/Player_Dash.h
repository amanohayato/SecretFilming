#pragma once
#include"PlayerState.h"

class Player_Dash : public PlayerState {
public:
	Player_Dash(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};