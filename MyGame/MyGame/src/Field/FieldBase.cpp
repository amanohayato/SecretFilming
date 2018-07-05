#include "FieldBase.h"
#include<DxLib.h>
#include"../Math/Vector3.h"
#include"../Define.h"
#include"../Graphic/Shader/ShaderManager.h"

// �R���X�g���N�^
FieldBase::FieldBase(int field, int skybox) :
	field_(field), skyBox_(skybox), mesh_(field_), out_(skybox){
	//���f�����ݒ肳��Ă��Ȃ�������Ԃ�
	if (field_ < 0 || skyBox_<0)return;

	// �t�B�[���h�̍��W�w��
	MV1SetPosition(field_,Vector3::Zero);
	// �t�B�[���h�̊g�嗦�w��
	MV1SetScale(field_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));

	// �X�J�C�{�b�N�X�̍��W�w��
	MV1SetPosition(skyBox_, Vector3::Zero);
	// �X�J�C�{�b�N�X�̊g�嗦�w��
	MV1SetScale(skyBox_, Vector3::One*2.f*FIELD_SCALE);
}

// �X�V
void FieldBase::update(float deltaTime) {
	if (field_ < 0 || skyBox_<0)return;
}

// �`��
void FieldBase::draw() const {
	if (field_ < 0 || skyBox_<0)return;

	// �X�J�C�{�b�N�X�̕`��
	MV1DrawModel(skyBox_);
	// �t�B�[���h�̕`��
	MV1DrawModel(field_);
}

// �t�B�[���h�̃n���h���擾
int FieldBase::modelHandle() {
	return field_;
}

CollisionMesh& FieldBase::getMesh()
{
	return mesh_;
}

CollisionMesh & FieldBase::getOutMesh()
{
	return out_.mesh_;
}
