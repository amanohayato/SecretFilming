#pragma once
#include"../../../UI/UIManager.h"
#include"../../../Graphic/TextBox.h"
#include"../../../Actor/Other/Confirm.h"


class Performance {
public:

	Performance();
	void start();
	void update(float deltaTime);
	void draw()const;
	void end();
	void setWorld(IWorld* world);

private:
	TextBox textBox_{4};
	float count = 0;
	IWorld*	world_{ nullptr };
	Confirm* confirm_;
};