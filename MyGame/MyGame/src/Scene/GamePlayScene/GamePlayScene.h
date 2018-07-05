#pragma once
#include"../Scene.h"
#include"../../World/World.h"
#include"../../Actor/Other/CarCamera.h"
#include"../../Actor/Car/CarGenerateManager.h"
#include"../../Actor/Citizen/CitizenGenerateManager.h"
#include"../../Graphic/BloomEffect.h"
#include"../../Scene/SubScene/Performance/Performance.h"

class Player;
class EventManager;
class SubScene;

class GamePlayScene:public Scene {
public:
	GamePlayScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw()override;
	//isEndがtrueになった後の処理
	virtual void end() override;

	// ポーズシーンの状態を変更する
	void changeState(SubSceneType next);

private:
	World world_;
	std::shared_ptr<Player> player_;
	CarGenerateManager cagm_{};
	CitizenGenerateManager cigm_{};
	EventManager* mEventManager_;
	Performance performance_{};

	// サブシーンの状態の種類
	std::map<SubSceneType, std::shared_ptr<SubScene>> states_;

	// 今のサブシーンの状態
	std::shared_ptr<SubScene> curState_;

	// ゲームの一時停止フラグ
	bool stopGame_{ false };
};