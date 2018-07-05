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

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

	void setActiveCamera(bool isActive);
	void setActiveMap(bool isActive);

private:

	// �e�v�f
	ActorPtr player_;

	std::shared_ptr<CameraApp> cameraApp_;
	std::shared_ptr<MapApp> mapApp_;
};