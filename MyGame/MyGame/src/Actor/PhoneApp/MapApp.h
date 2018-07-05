#pragma once
#include"../Actor.h"
#include"../../UI/FieldMap.h"

// マップアプリの状態
enum class MapAppState
{
	// スリープ中
	Sleep,

	// 起動中
	Active
};

class MapApp : public Actor
{
public:
	MapApp(IWorld * world, ActorPtr player);
	~MapApp();
	void initialize();

	void update(float deltaTime);

	void draw()const;

	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;

	// マップアプリの状態の変更
	void changeState(MapAppState state);

	void active();
	void sleep();
private:

	// 現在のマップアプリの状態
	MapAppState curState_{ MapAppState::Sleep };
	FieldMap fieldMap_;
	// 親要素
	ActorPtr player_;

	int mapScreen_{ -1 };


};