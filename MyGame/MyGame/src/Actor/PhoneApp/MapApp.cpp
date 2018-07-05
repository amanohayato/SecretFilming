#include "MapApp.h"
#include"../../Define.h"
#include"../../Math/Easing.h"


MapApp::MapApp(IWorld * world, ActorPtr player) :
	Actor(world, "MapApp", Vector3::Zero, std::make_shared<DummyBody>()), fieldMap_{ world }
{
	player_ = player;
}

MapApp::~MapApp()
{
	DeleteGraph(mapScreen_);
}

void MapApp::initialize()
{
	fieldMap_.initialize();
	mapScreen_ = MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void MapApp::update(float deltaTime)
{
	// 現在の状態がスリープ状態なら処理を行わない
	if (world_->getMapAmount() < 0.99f) {
		if(world_->getMapAmount()<=0.01f)fieldMap_.pin_reset();
		
		return;
	}
	fieldMap_.update(deltaTime);


}

void MapApp::draw() const
{
	// 現在の状態がスリープ状態なら処理を行わない
	if (world_->getMapAmount()<0.01f) return;

	world_->addDrawFunction([&] {
		SetDrawScreen(mapScreen_);
		SetBackgroundColor(255, 245, 245);
		ClearDrawScreen();
		Vector2 lerp = Vector2::Lerp(Vector2(0.f, (float)WINDOW_HEIGHT), Vector2::Zero, MathHelper::Smoothstep(0.0f, 1.0f, world_->getMapAmount()));

		fieldMap_.draw(Vector2{ 200.0f,50.0f });

		SetDrawScreen(DX_SCREEN_BACK);
		SetBackgroundColor(0, 0, 0);
		DrawGraph(0, (int)lerp.y, mapScreen_, TRUE);
	});
}

void MapApp::receiveMessage(EventMessage message, void * param)
{
}

// マップアプリの状態の変更
void MapApp::changeState(MapAppState state)
{
	curState_ = state;
}

void MapApp::active()
{
	changeState(MapAppState::Active);
}

void MapApp::sleep()
{
	changeState(MapAppState::Sleep);
}
