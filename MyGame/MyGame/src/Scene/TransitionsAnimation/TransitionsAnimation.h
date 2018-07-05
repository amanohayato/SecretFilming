#pragma once
#include"../../ID/EnumIDs.h"
#include "../../Graphic/Sprite.h"

class TransitionsAnimation {
public:
	virtual ~TransitionsAnimation() {}

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw()const = 0;

	virtual bool isEnd() const { return isEnd_; }

	virtual bool canUpdateScene() const { return canUpdateScene_; }

	virtual bool isChangeScene() = 0;

	//ã§í ÇÃèâä˙âª
	void baseInit() {
		isEnd_ = false;
	}

protected:
	bool isEnd_{ false };

	bool canUpdateScene_{ false };

	bool isChangeScene_{ false };
};