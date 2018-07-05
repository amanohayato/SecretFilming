#pragma once

#include"../SubScene.h"

class Title : public SubScene {
public:

	Title();
	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

private:

	int sinCount_{ 0 };
};