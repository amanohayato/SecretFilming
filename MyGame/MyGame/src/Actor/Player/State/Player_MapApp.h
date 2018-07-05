#pragma once
#include"PlayerState.h"

class Player_MapApp : public PlayerState {
public:
	Player_MapApp(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
};