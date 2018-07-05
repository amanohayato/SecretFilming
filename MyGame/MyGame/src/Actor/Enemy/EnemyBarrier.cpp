#include "EnemyBarrier.h"
#include"../../Graphic/Model.h"
#include"../../Sound/Sound.h"

// �G�l�~�[�̃o���A�N���X
// �S���FHo Siu Ki�i�����Q�j

// �R���X�g���N�^
EnemyBarrier::EnemyBarrier(ActorPtr target, ActorPtr enemy,Vector3 position, Matrix rotation, bool isStop) :
	Actor(nullptr, "EnemyBarrier", position, rotation),isStop_(isStop)
{
	target_ = target;
	enemy_ = enemy;
	Vector3 dir = target_->getPosition() - enemy_->getPosition();
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
	position_ = enemy_->getPosition() + dir.Normalize() * 6.0f;
	//�o���ASE
	Sound::GetInstance().Play3DSE(SE_ID::GUARD_SE, (VECTOR*)&position_);
}

// ������
void EnemyBarrier::initialize()
{
}

// �X�V
void EnemyBarrier::update(float delta_time)
{
	if (timer_ <= 0.0f)
	{
		dead();
	}

	timer_ -= delta_time;
	if (isStop_)return;
	Vector3 dir = target_->getPosition() - enemy_->getPosition();
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
	position_ = enemy_->getPosition() + dir.Normalize() * 6.0f;
}

// �`��
void EnemyBarrier::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_BARRIER, Matrix(rotation_).Translation(position_));
}