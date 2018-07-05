#include "CameraActor.h"
#include"../../Input/InputChecker.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include"../../Field/FieldBase.h"
#include"../../Math/Easing.h"

CameraActor::CameraActor(IWorld * world,const Vector3& position, IBodyPtr body) :
	Actor(world, "Camera", position, body),target_(), prevRotation_(rotation_)
{
}

void CameraActor::initialize()
{
	isActive_ = true;
	cameraDistance_ = defaultCameraDistance;
	rotate_ = Vector2::Zero;//�J�����̉�]
	movefwPos_ = Vector3::Zero;
	moverhPos_ = Vector3::Zero;
	camerafwPos_ = Vector3::Zero;
	setUpVector(Vector3::Up);
	prevUpVector_ = Vector3::Up;
	cameraupLerpTimer_ = 1.0f;
	target_.reset();
	Camera::GetInstance().SetRange(0.1f, 10000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
}

void CameraActor::update(float deltaTime)
{
	cameraupLerpTimer_ = min(cameraupLerpTimer_ + deltaTime, 1.0f);
	cameraDistance_ = MathHelper::Lerp(cameraDistance_, nextCameraDistance_, cameraupLerpTimer_);


	lerpTimer_ = min((lerpTimer_ + deltaTime / LerpTime), 1.0f);

	Vector3 movePos = Vector3::Zero;//���t���[���p�̃J�����ړ��x�N�g��

	//���͂�����Ă���
	Vector2 move = InputChecker::GetInstance().RightStick()*3.f;
	if (move.Length() > 0.3f) {
		rotate_ += move;
		//�J�����̉�]���E��ݒ肷��
		rotate_.y = MathHelper::Clamp(rotate_.y, -80.0f, 80.0f);
	}

	//���ʍ��W����Ƃ����ʒu�␳���s��
	movePos.x = -cameraDistance_*MathHelper::Sin(rotate_.x) * MathHelper::Cos(rotate_.y);
	movePos.y = -cameraDistance_*MathHelper::Sin(rotate_.y);
	movePos.z = -cameraDistance_*MathHelper::Cos(rotate_.x) * MathHelper::Cos(rotate_.y);

	movePos = movePos*rotation_;

	//�v���C���[�p�̐ݒ�
	camerafwPos_ = (-movePos).Normalize();

	////////////�����𒲂ׂāA����ɉ�������]�ʂɂ��Ă�����K�v������
	//////////float dot = Vector3::Dot(Vector3::Up, upVector_);
	//////////Vector3 axis = Vector3::Cross(Vector3::Up, upVector_);
	//////////axis = axis.Normalize();

	//////////test = axis;
	////////////movePos����]�����āA������Up�x�N�g���ɍ��킹��
	//////////float angle = MathHelper::ACos(dot);
	//movePos = movePos* Matrix::CreateFromAxisAngle(axis, angle);

	//�v���C���[�p�̐ݒ�
	Vector3 mp = movePos;
	mp.Normalize();
	Vector3 left = Vector3::Normalize(Vector3::Cross(upVector_, mp));
	Vector3 backward = Vector3::Cross(left, upVector_);

	//�ړ�����ݒ肷��
	movefwPos_ = -backward;
	moverhPos_ = -left;


	//�ʒu��Ԃ��s��
	position_ = Vector3::Lerp(position_,target_.lock()->getPosition() + movePos,0.9f);

	//�J�����ʒu���Z�b�g����
	Vector3 cameraPos=position_;

	Vector3 hitpos;
	if (world_->getFieldOnly()->getMesh().collide_line(position_, target_.lock()->getPosition(), (VECTOR*)&hitpos)) {
		cameraPos = hitpos + Vector3(target_.lock()->getPosition() - position_).Normalize()*5.0f;
	}

	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(target_.lock()->getPosition() + moveTargetPos_);
	float easePoint = Easing::EaseOutQuad(lerpTimer_, 0.0f, 1.0f, 1.0f);
	test = easePoint;
	Camera::GetInstance().Up.Set(Matrix::Lerp(prevRotation_, rotation_, easePoint).Up());
	Camera::GetInstance().Update();


}

void CameraActor::draw() const
{
	//DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT*0.8f, GetColor(255, 255, 255), "%f", test);
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + test, GetColor(255, 0, 0));
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Up(), GetColor(0, 255, 0));
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Forward(), GetColor(0, 0, 255));
}

void CameraActor::end()
{
}

void CameraActor::setTarget(const std::shared_ptr<Actor>& target)
{
	target_ = target;
}

void CameraActor::setUpVector(const Vector3 & up)
{
	if (MathHelper::ACos(Vector3::Dot(Vector3::Normalize(upVector_), Vector3::Normalize(up))) >= 5.0f) {
		lerpTimer_ = 0.0f;
		prevRotation_ = rotation_;
		prevUpVector_ = upVector_;
	}
	upVector_ = up;
	rotation_.Up(up);
	rotation_.NormalizeRotationMatrix_BaseUp();
}

Vector3 CameraActor::getUpVector() const
{
	return upVector_;
}

void CameraActor::inCamera(float distance)
{
	cameraupLerpTimer_ = 0.0f;
	nextCameraDistance_ = distance;
}

void CameraActor::outCamera()
{
	cameraupLerpTimer_ = 0.0f;
	nextCameraDistance_ = defaultCameraDistance;
}
