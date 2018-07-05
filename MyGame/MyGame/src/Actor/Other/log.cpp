//#include "CameraActor.h"
//#include"../../Input/InputChecker.h"
//
////カメラを離す距離
//const float defaultCameraDistance = 30.0f;
//CameraActor::CameraActor(IWorld * world, const Vector3& position, IBodyPtr body) :
//	Actor(world, "Camera", position, body), target_()
//{
//}
//
//void CameraActor::initialize()
//{
//	isActive_ = true;
//	cameraDistance_ = defaultCameraDistance;
//	rotate_ = Vector2::Zero;//カメラの回転
//	movefwPos_ = Vector3::Zero;
//	moverhPos_ = Vector3::Zero;
//	camerafwPos_ = Vector3::Zero;
//	setUpVector(Vector3::Up);
//	target_.reset();
//	Camera::GetInstance().SetRange(0.1f, 1000.0f);
//	Camera::GetInstance().SetViewAngle(60.0f);
//}
//
//void CameraActor::update(float deltaTime)
//{
//	Vector3 movePos = Vector3::Zero;//現フレーム用のカメラ移動ベクトル
//
//									//入力を取ってきて
//	Vector2 move = InputChecker::GetInstance().RightStick()*3.f;
//	if (move.Length() > 0.2f) {
//		rotate_ += move;
//		//カメラの回転限界を設定する
//		rotate_.y = MathHelper::Clamp(rotate_.y, -80.0f, 80.0f);
//	}
//	//rotation_ = Matrix(Matrix::Identity)*Matrix::CreateFromAxisAngle(rotation_.Up(), rotate_.);
//
//	//球面座標を基準とした位置補正を行う
//	movePos.x = -cameraDistance_*MathHelper::Sin(rotate_.x) * MathHelper::Cos(rotate_.y);
//	movePos.y = -cameraDistance_*MathHelper::Sin(rotate_.y);
//	movePos.z = -cameraDistance_*MathHelper::Cos(rotate_.x) * MathHelper::Cos(rotate_.y);
//
//	test = movePos;
//
//	//rotation_ = Matrix(Matrix::Identity)*Matrix::CreateRotationX(movePos.x)*Matrix::CreateRotationY(movePos.y)*Matrix::CreateRotationZ(movePos.z);
//
//	//movePos = movePos*Matrix(Matrix::Identity).Up(upVector_).NormalizeRotationMatrix();
//	/*
//	movePos.x = cameraDistance_*MathHelper::Sin(rotate_.y) * MathHelper::Cos(rotate_.x);
//	movePos.y = -cameraDistance_*MathHelper::Cos(rotate_.y);
//	movePos.z = -cameraDistance_*MathHelper::Sin(rotate_.y) * MathHelper::Sin(rotate_.x);
//	rotate.X = Math.Cos(x) * Math.Cos(y);
//	rotate.Y = Math.Sin(y);
//	rotate.Z = Math.Sin(x) * Math.Cos(y);
//	*/
//
//	//// 方向ボタン「↑」を押したときのプレイヤーの移動ベクトルはカメラの視線方向からＹ成分を抜いたもの
//	//UpMoveVec = VSub(cam.Target, cam.Eye);
//	//UpMoveVec.y = 0.0f;
//
//	//// 方向ボタン「←」を押したときのプレイヤーの移動ベクトルは上を押したときの方向ベクトルとＹ軸のプラス方向のベクトルに垂直な方向
//	//LeftMoveVec = VCross(UpMoveVec, VGet(0.0f, 1.0f, 0.0f));
//
//	camerafwPos_ = (-movePos).Normalize();
//
//	//向きを調べて、それに応じた回転量にしてあげる必要がある
//	float dot = Vector3::Dot(Vector3::Up, upVector_);
//	Vector3 axis = Vector3::Cross(Vector3::Up, upVector_);
//
//
//	float angle = MathHelper::ACos(dot);
//	movePos = movePos* Matrix::CreateFromAxisAngle(axis, angle);
//
//
//	//movePos = movePos*Matrix::CreateWorld(Vector3::Zero, -backward, upVector_);
//	Vector3 mp = movePos;
//	mp.Normalize();
//	//float angle = MathHelper::ACos(Vector3::Dot(Vector3::Up, mp));
//	Vector3 left = Vector3::Normalize(Vector3::Cross(upVector_, mp));
//	Vector3 backward = Vector3::Cross(left, upVector_);
//
//	movefwPos_ = -backward;
//	moverhPos_ = -left;
//
//
//	//現在のカメラのUpを基準にして、二次元ベクトルを作る方法を考える
//	/*
//	mp = mp*Matrix::CreateFromAxisAngle(axis, -angle);
//
//	//auto i = Matrix::InvertFast(Matrix(Matrix::Identity).Up(mp).NormalizeRotationMatrix());
//	mp.z = 0.0f;
//	mp = mp*Matrix::CreateFromAxisAngle(axis, angle);
//
//	//mp-=upVector_;
//
//	*/
//
//	//movefwPos_ = -mp;
//	//moverhPos_ = Vector3::Cross(mp, upVector_);
//	position_ = Vector3::Lerp(position_, target_.lock()->getPosition() + movePos, 0.9f);
//	Camera::GetInstance().Position.Set(position_);
//	Camera::GetInstance().Target.Set(target_.lock()->getPosition() + moveTargetPos_);
//	Camera::GetInstance().Up.Set(upVector_);
//	Camera::GetInstance().Update();
//
//
//}
//
//void CameraActor::draw() const
//{
//	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + test, GetColor(255, 0, 0));
//	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Up(), GetColor(0, 255, 0));
//	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Forward(), GetColor(0, 0, 255));
//}
//
//void CameraActor::end()
//{
//}
//
//void CameraActor::setTarget(const std::shared_ptr<Actor>& target)
//{
//	target_ = target;
//}
//
//void CameraActor::setUpVector(const Vector3 & up)
//{
//	upVector_ = up;
//	//rotation_.Up(up);
//	//rotation_.NormalizeRotationMatrix_BaseUp();
//}
//
//Vector3 CameraActor::getUpVector() const
//{
//	return upVector_;
//}
