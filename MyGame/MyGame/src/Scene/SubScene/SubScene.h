#pragma once
#include "../../ID/EnumIDs.h"

// エントランスシーンの状態のテンプレ
class SubScene {

public:
	virtual ~SubScene() {}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw()const = 0;
	virtual void end() = 0;

	bool isChangeScene() const { return isChangeScene_; }
	SceneType nextScene() const { return nextScene_; }

	bool isChangeSubScene() const { return isChangeSubScene_; }
	SubSceneType nextSubScene() { return nextSubScene_; }

	bool isGameEnd() const { return isGameEnd_; }

protected:

	virtual void baseInit()
	{
		isChangeScene_ = false;
		isChangeSubScene_ = false;
		isGameEnd_ = false;
	}

protected:

	bool isChangeScene_;
	SceneType nextScene_;

	bool isChangeSubScene_;
	SubSceneType nextSubScene_;

	bool isGameEnd_;
};