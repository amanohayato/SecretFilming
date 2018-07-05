#include "PlayerState.h"
#include"../../../Sound/Sound.h"
#include"../../../Input/InputChecker.h"
#include"../../../World/IWorld.h"
#include"../../../Scene/Manager/GameDataManager.h"
#include"../Player.h"

PlayerState::PlayerState(ActorPtr player) :
	player_(player),fpsCam_(static_cast<Player*>(player.get())->getFPSCamera())
{
}

PlayerState::PlayerState(IWorld * world, ActorPtr player) :
	world_(world), player_(player), fpsCam_(static_cast<Player*>(player.get())->getFPSCamera())
{
}

void PlayerState::start()
{
}

void PlayerState::update(float deltaTime)
{
}

void PlayerState::end()
{
}

void PlayerState::input_to_move(float deltaTime)
{
	fpsCam_.getsens() = GameDataManager::getInstance().getCameraSens();

	// �O�t���[���n�ʂɐݒu���Ă�����d�̗͂͂��[���ɂ���
	if (prevfloor_)gravity_ = 0.0f;
	// �R���g���[���[�̃X�e�B�b�N�̌X������擾
	Vector2 stickDirection = InputChecker::GetInstance().Stick();

	// �����X�e�B�b�N�̌X�����0.2�ȉ���������
	if (stickDirection.Length() <= 0.2f) {


		// �Đ����Ă���_�b�V��SE�C���X�^���X���~����
		Sound::GetInstance().StopSE(SE_ID::RUN_SE);

		// ���̊֐����I��
		return;
	}

	// �_�b�V��SE�C���X�^���X���Đ�����
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::RUN_SE);
	if (getState() == Player_State_ID::Dash) {
		//�_�b�V��SE���Đ�
		Sound::GetInstance().SetRate(SE_ID::RUN_SE,50000);
	}
	else {
		Sound::GetInstance().ReSetRate(SE_ID::RUN_SE);
	}
	// ���Ƀv���C���[�̍��W��ύX����̂Ɏg�p��������E���x�̒l��p�� 
	Vector3 frameVelocity = Vector3::Zero;

	// �R���g���[���[�̃X�e�B�b�N�̌X���Ǝ��g�̉�]�������g��
	frameVelocity = (Vector3{ stickDirection.x, 0.0f, stickDirection.y } * moveSpeed_) * fpsCam_.getRotation();

	// �P�t���[���̌o�ߎ��ԕ��̕␳��������
	frameVelocity *= deltaTime;

	// ���g�̍��W�̒l�ɕ����E���x�̒l��K�p�i�������Œ��� position �̒l�ɓK�p���đ��v���ȁH�j
	player_->getPosition() += frameVelocity;
	player_->getPosition().z = MathHelper::Clamp(player_->getPosition().z,160.0f,GameDataManager::getInstance().getMapSize().y);
}

void PlayerState::setFloor(bool prevfloor)
{
	prevfloor_ = prevfloor;
}

Player_State_ID PlayerState::getState() const
{
	return state_;
}

Player_State_ID PlayerState::getNextState() const
{
	return nextState_;
}

FPSCamera PlayerState::getFPSCam() const
{
	return fpsCam_;
}


void PlayerState::setObjct(const Vector3 & position, const Matrix & rotation)
{
	objPositionStr_ = position;
	objRotation_ = rotation;
	fpsCam_.SetRotation(rotation);
}

float PlayerState::getGravity() const
{
	return gravity_;
}

bool PlayerState::isCamera() const
{
	return isCamera_;
}

bool PlayerState::isAction() const
{
	return isAction_;
}

void PlayerState::setIsWatch(const bool& isWatch)
{
	isWatch_ = isWatch;
}

bool PlayerState::getIsWatch() const
{
	return isWatch_;
}

void PlayerState::setFPSCam(FPSCamera cam)
{
	fpsCam_ = cam;
}