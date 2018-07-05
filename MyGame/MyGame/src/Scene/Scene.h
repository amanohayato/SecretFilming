#pragma once
#include"../ID/EnumIDs.h"

//シーンテンプレート
class Scene {
public:
	virtual ~Scene() {}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw()const = 0;
	virtual void lateDraw() {}
	//isEndがtrueになった後の処理
	virtual void end() = 0;

	virtual bool isEnd() const { return isEnd_; }
	virtual bool isGameEnd() const { return isGameEnd_; }

	virtual SceneType nextScene()const { return next_; }

	virtual TransitionsAnimeType transitionsAnimeType()const { return transitionsAnimeType_; }

	//共通の初期化
	void baseInit() {
		isEnd_ = false;
		isGameEnd_ = false;
	}

protected:
	bool isEnd_{ false };
	bool isGameEnd_{ false };
	SceneType next_{ SceneType::SCENE_GAMEPLAY };
	TransitionsAnimeType transitionsAnimeType_{ TransitionsAnimeType::None };
};