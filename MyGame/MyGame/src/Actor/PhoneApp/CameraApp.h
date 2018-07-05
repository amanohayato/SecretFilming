#pragma once
#include"../Actor.h"

// カメラアプリの状態
enum class CameraAppState
{
	// スリープ中
	Sleep,

	// 起動中
	Active
};

class CameraApp : public Actor
{
public:

	CameraApp(IWorld * world, ActorPtr player);

	void initialize();

	void update(float deltaTime);

	void draw()const;

	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;

	// スコアを計算する関数
	int scoreCalculation();

	// カメラアプリの状態の変更
	void changeState(CameraAppState state);

	void active();
	void sleep();
private:

	// 現在のカメラアプリの状態
	CameraAppState curState_{ CameraAppState::Sleep };

	// 親要素であるプレイヤー
	ActorPtr player_;

	// 写真の撮影最大距離
	static const float shootingRange_;

	// 写真の撮影最大角度
	static const float shootingAngle_;

	float frameSetRate{ 0.0f };//枠セットまでの時間
};