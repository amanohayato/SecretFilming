#include "CarCamera.h"

CarCamera::CarCamera(IWorld * world, const Vector3 & position, IBodyPtr body):
	Actor(world,"CarCam",position,body)
{
	Camera::GetInstance().SetRange(0.1f, 10000.0f);
	//Camera::GetInstance().SetViewAngle(60.0f);
}

void CarCamera::setTarget(std::weak_ptr<Actor> target)
{
	target_ = target;
}

void CarCamera::update(float deltaTime)
{
	if (target_.expired())return;

	//Camera::GetInstance().Position.Set(target_.lock()->getPosition() + Vector3{ 0.0f,600.0f,0.0f });
	Camera::GetInstance().Position.Set(Vector3{ 0.0f,1800.0f,0.0f });
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Forward);
	Camera::GetInstance().Update();
	SetupCamera_Ortho(2500.0f);

}
