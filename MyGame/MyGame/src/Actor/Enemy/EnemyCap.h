#pragma once
#include"../Actor.h"

class EnemyBase;

class EnemyCap :public Actor {
	enum class State {
		wear,
		fall,
		stop,
		pick,
	};
public:
	EnemyCap(IWorld* world,std::shared_ptr<EnemyBase> enemy);

	virtual void initialize()override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;

	void beginfall(const Vector3& dir);
	void pickcap();
	void endfall();

	void wear(float deltaTime);
	void fall(float deltaTime);
	void stop(float deltaTime);
	void pick(float deltaTime);
private:
	std::function<void()> _drawFunc;
	std::weak_ptr<EnemyBase> _target;

	Vector3 _fallDir{ Vector3::Zero };

	State _state;
};