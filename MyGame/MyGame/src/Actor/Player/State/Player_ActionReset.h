#ifndef PLAYER_ACTION_RESET_H_
#define PLAYER_ACTION_RESET_H_

#include"PlayerState.h"

class Player_ActionReset : public PlayerState {
public:
	Player_ActionReset(ActorPtr player);
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void end() override;
private:
	float t_{ 0.0f };
};
#endif // !PLAYER_ACTION_NULL_H_