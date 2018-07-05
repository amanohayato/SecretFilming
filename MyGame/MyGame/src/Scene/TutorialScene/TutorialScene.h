#pragma once
#include<vector>
#include<memory>
#include"../Scene.h"
#include"../../World/World.h"
#include"../../Actor/Car/CarGenerateManager.h"
#include"../../Actor/Citizen/CitizenGenerateManager.h"

class Player;

class TutorialEnemy;

class TutorialCommand;

class TutorialScene : public Scene
{
public:
	TutorialScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw()override;
	virtual void end() override;

	void setTutorialCommand();
	void changeTutorialCommand();

private:

	// 画像点滅用カウント
	int sinCount_{ 0 };

	// 経過時間（秒）の値
	float elapsedTime_{ 0.0f };

	// 何秒後にデモムービーシーンに移行するか
	const float goDemoSceneTime_{ 15.0f };

	// チュートリアルのコマンドリスト
	std::vector<std::shared_ptr<TutorialCommand>> commandList_;
	
	// 現在のコマンド番号
	int curIndex_{ 0 };

	// 
	World world_;
	std::shared_ptr<Player> player_;
	std::shared_ptr<TutorialEnemy> enemy_;
	CarGenerateManager cagm_{};
	CitizenGenerateManager cigm_{};
};
