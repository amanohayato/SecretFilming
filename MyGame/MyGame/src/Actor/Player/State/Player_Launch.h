#pragma once
#include"PlayerState.h"

class Player_Launch : public PlayerState {
public:
	Player_Launch(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};