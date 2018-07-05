#include "FPSCamera.h"
#include"../../../Camera/Camera.h"

FPSCamera::FPSCamera()
{
	Camera::GetInstance().SetRange(1.0f, 5000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
	rotation_ = Matrix::Identity;
}

void FPSCamera::initialize(Matrix & rotation)
{
	rotationMat_.initialize(rotation);
}

void FPSCamera::update(Vector3 position) {
	rotation_ = rotationMat_.update();
	position += Vector3::Up * 3;
	camera_update(position, rotation_);
}
void FPSCamera::EventUpdate(Vector3 position) {
	rotation_ = rotationMat_.eventUpdate();
	position += Vector3::Up * 3;
	camera_update(position, rotation_);
}
void FPSCamera::StartUpdate(Vector3 position,Matrix & rotation)
{
	rotation_ = rotation;
	position += Vector3::Up * 3;
	camera_update(position, rotation_);
}
void FPSCamera::ResetUpdate(Vector3 position)
{
	rotation_ = rotationMat_.resetOnlyUpdate();
	position += Vector3::Up * 3;
	camera_update(position, rotation_);
}
void FPSCamera::camera_update(const Vector3 & position, const Matrix & rotation)
{
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(position + rotation.Forward());
	Camera::GetInstance().Up.Set(rotation.Up());
	Camera::GetInstance().Update();
}
Matrix FPSCamera::getRotation() const{
	return rotation_;
}
void FPSCamera::normalReset() {
	rotationMat_.NormalReset(rotation_);
}
void FPSCamera::eventReset() {
	rotationMat_.EventReset(rotation_);
}
float & FPSCamera::getsens()
{
	return rotationMat_.sens();
}
void FPSCamera::SetRotation(const Matrix& mat) {
	rotationMat_.SetEventRotation(mat);
}