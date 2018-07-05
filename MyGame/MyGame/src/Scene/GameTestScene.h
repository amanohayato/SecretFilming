#pragma once
#include"Scene.h"
#include"../Field/PointGenerator.h"
#include"../World/World.h"
#include"../Actor/Other/CarCamera.h"

class Player;
class GameTestScene :public Scene {
public:
	GameTestScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void lateDraw()override;
	//isEnd‚ªtrue‚É‚È‚Á‚½Œã‚Ìˆ—
	virtual void end() override;

private:
	World world_;
	std::shared_ptr<Player> player_;
};