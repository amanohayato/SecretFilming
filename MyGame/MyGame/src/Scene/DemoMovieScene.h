#pragma once
#include "Scene.h"

class DemoMovieScene :public Scene
{
public:
	DemoMovieScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end() override;

private:

	int sinCount_{ 0 };//点滅カウント

};