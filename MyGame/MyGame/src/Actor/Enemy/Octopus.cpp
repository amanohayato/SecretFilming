#include "Octopus.h"
#include "../../Graphic/Model.h"
#include "EnemyBarrier.h"

// �^�R�^�F���l�N���X
// �S���FHo Siu Ki�i�����Q�j

// �R���X�g���N�^
Octopus::Octopus(IWorld * world, const Vector3 & position, const IBodyPtr & body)
	: EnemyBase(world, position, body)
{
	//animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));	// ���f����ǂݍ���
}

// ������
void Octopus::initialize()
{
	EnemyBase::initialize();
}

// �ڐG����
void Octopus::onCollide(Actor& other)
{
	if (other.isAction()) return;
	if (other.getName() == "Player" || other.getName() == "Car")
	{
		// ��������v���[���[�ւ̕����x�N�g��
		Vector3 direction_to_player = other.getPosition() - position_;

		other.receiveMessage(EventMessage::Hit_Enemy,(void*)&direction_to_player);

		on_Barrier(world_->findActor(other.getName()), world_->findActor("Enemy"));
	}
	if (other.getName() == "Player") {
		if(state_ != EnemyState::Escape&&state_ != EnemyState::DiscoveryStart && !is_event_)change_state(EnemyState::DiscoveryStart);
	}
}