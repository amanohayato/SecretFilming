#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"
#include"../Cat/AbductCat.h"



class GameOverUfo :public Actor {
	enum class State {
		start,
		down,
		abduct,
		up,
		end,
	};
public:
	GameOverUfo(IWorld* world, const Vector3& start, const Vector3& goal);
	virtual ~GameOverUfo() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	void setTarget(const std::shared_ptr<Actor>& actor);

	void begin();
private:
	void start(float deltaTime);
	void down(float deltaTime);
	void abduct(float deltaTime);
	void up(float deltaTime);
	void end(float deltaTime);

private:
	State mState;
	Vector3 mStartPos;	//スタート
	Vector3 mGoalPos;	//ゴール
	float mLerpTime;	//線形補間タイム

	float lightScale{ 0.0f };
	bool isStart_{ false };
	Vector3 direction_;
	Vector3 targetStartPos_{ Vector3::Zero };
	std::weak_ptr<Actor> target_{};
	std::function<void(float)> func_{};
};