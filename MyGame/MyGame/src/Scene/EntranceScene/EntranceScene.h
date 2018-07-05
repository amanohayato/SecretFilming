#pragma once
#include<map>
#include<memory>
#include"../Scene.h"
#include"../../World/World.h"
#include"../../Actor/Car/CarGenerateManager.h"
#include"../../Actor/Citizen/CitizenGenerateManager.h"

class SubScene;

class TitleCamera;
class TitleUfoFactory;

// エントランスシーン
class EntranceScene :public Scene {

public:
	EntranceScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw() override;
	virtual void end() override;

	// エントランスシーンの状態を変更する
	void changeState(SubSceneType next);

private:

	// サブシーンの種類
	std::map<SubSceneType, std::shared_ptr<SubScene>> subScenes_;

	// 現在のサブシーンの状態
	std::shared_ptr<SubScene> curSubScene_;

	// 画像点滅用カウント
	int sinCount_{ 0 };

	// 経過時間（秒）の値
	float elapsedTime_{ 0.0f };

	// 何秒後にデモムービーシーンに移行するか
	const float goDemoSceneTime_{ 15.0f };

	// タイトルの背景に必要なクラスたち
	World world_;
	std::shared_ptr<TitleCamera> titleCamera_;
	std::shared_ptr<TitleUfoFactory> titleUfoFactory_;
	CarGenerateManager cagm_{};
	CitizenGenerateManager cigm_{};
};