#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include"../../Method/CountTimer.h"
//#include"Base/MatrixRotation.h"
#include "../Player/Base/FPSCamera.h"
#include<memory>


class TitleCamera :public Actor {

public:
	TitleCamera(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	TitleCamera(IWorld* world, const Vector3& position, const Matrix& rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;

	virtual void onCollide(Actor& other);
	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;
	
private:
	// カメラ用の回転行列
	Matrix cameraRotation_{ Matrix::Identity };
	FPSCamera fpsCam_;


	float sinCount_{ 0 };
};