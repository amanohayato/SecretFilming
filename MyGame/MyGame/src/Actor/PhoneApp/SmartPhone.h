#pragma once
#include"../Actor.h"

class CameraApp;
class MapApp;

class SmartPhone : public Actor
{
public:
	SmartPhone(IWorld * world, ActorPtr player);
	
	void initialize();

	void update(float deltaTime);

	void draw()const;

	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;

	void setActiveCamera(bool isActive);
	void setActiveMap(bool isActive);

private:

	// 親要素
	ActorPtr player_;

	std::shared_ptr<CameraApp> cameraApp_;
	std::shared_ptr<MapApp> mapApp_;
};