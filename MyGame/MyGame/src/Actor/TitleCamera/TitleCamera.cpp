#include "TitleCamera.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../../Field/Building/BuildingBase.h"
#include"../Other/CameraActor.h"
#include"../../Field/FieldBase.h"
#include"../../Graphic/AnimLoader.h"
#include"../../Graphic/Sprite.h"
#include"../../ID/EnumIDs.h"
#include"../../Define.h"
#include"../Other/CameraActor.h"
#include"../../Sound/Sound.h"
#include"../Player/Base/FPSCamera.h"
// #include"State\StateIncludeh.h"
#include"../PhoneApp//SmartPhone.h"

TitleCamera::TitleCamera(IWorld * world, const Vector3 & position, const IBodyPtr & body)
{
	name_ = "TitleCamera";
	//回転行列初期化
	rotation_ = Matrix::Identity;
	fpsCam_.initialize(rotation_);

	
}

TitleCamera::TitleCamera(IWorld * world, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body)
{
	fpsCam_.initialize(rotation_);
}

void TitleCamera::initialize()
{
}

void TitleCamera::update(float deltaTime)
{
	// 画面回転用のカウンタのカウントアップ
	sinCount_ = (float)(((int)(sinCount_* 10) + 1) % 3600) / 10;

	// 回転させる
	rotation_ = Matrix::CreateFromYawPitchRoll(-sinCount_ - 90, 45, 0);

	// 回転に合わせて原点を45°で見下ろす位置に移動
	position_ = Vector3(MathHelper::Cos(sinCount_) * 500.0f, 500, MathHelper::Sin(sinCount_) * 500.0f);

	// ステージの中央付近（マジックナンバー）に移動する
	position_ += Vector3(600, 0, 600);

	// カメラの更新を行う
	Camera::GetInstance().Position.Set(position_);
	Camera::GetInstance().Target.Set(position_ + rotation_.Forward());
	Camera::GetInstance().Up.Set(rotation_.Up());
	Camera::GetInstance().Update();
	cameraRotation_ = fpsCam_.getRotation();
	rotation_ = Matrix::CreateRotationY(-Matrix::Angle(cameraRotation_).y);
}

void TitleCamera::draw() const
{
}

void TitleCamera::onCollide(Actor & other)
{
}

void TitleCamera::receiveMessage(EventMessage message, void * param)
{
}
