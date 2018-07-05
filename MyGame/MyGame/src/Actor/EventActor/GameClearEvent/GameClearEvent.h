#pragma once
#include"../../Actor.h"
#include "../../Player/State/PlayerState.h"
#include"../../Enemy/EnemyBase.h"

class GameClearEvent : public Actor
{
public:

	GameClearEvent(IWorld * world,float goal_timer, const float goal_time, std::weak_ptr<EnemyBase> enemy);

	void initialize();

	void update(float delta_time) override;

	void draw()const;

	void car_ci_dead();

	//メッセージの受信
	//virtual void receiveMessage(EventMessage message, void* param) override;


private:
	const float goal_time_;//ゴールしてからリザルトに移行するまでの秒数
	float goal_timer_; //ゴールしてからリザルトに移行するまでの秒数カウント
	std::weak_ptr<EnemyBase>enemy_;//enemybasePtr
	const Vector3 camerapos_ = { 725.0f,11.0f,715.0f };
	float sirenvol_ = 0;
	
};