#include "SmartPhone.h"
#include "CameraApp.h"
#include "MapApp.h"

SmartPhone::SmartPhone(IWorld * world, ActorPtr player) :
	Actor(world, "SmartPhone", Vector3::Zero, std::make_shared<DummyBody>())
{
	player_ = player;
}

void SmartPhone::initialize()
{
	// カメラアプリを作成
	cameraApp_ = std::make_shared<CameraApp>(world_, player_);
	cameraApp_->initialize();

	// 地図アプリを作成
	mapApp_ = std::make_shared<MapApp>(world_, player_);
	mapApp_->initialize();

	// 作成したアプリの追加
	addChild(cameraApp_);
	addChild(mapApp_);
}

void SmartPhone::update(float deltaTime)
{

}

void SmartPhone::draw() const
{
}

void SmartPhone::receiveMessage(EventMessage message, void * param)
{
}

void SmartPhone::setActiveCamera(bool isActive)
{
	(isActive) ? cameraApp_->active() : cameraApp_->sleep();
}

void SmartPhone::setActiveMap(bool isActive)
{
	(isActive) ? mapApp_->active() : mapApp_->sleep();
}
