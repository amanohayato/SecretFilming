#include "Octopus.h"
#include "../../Graphic/Model.h"
#include "EnemyBarrier.h"

// タコ型宇宙人クラス
// 担当：Ho Siu Ki（何兆祺）

// コンストラクタ
Octopus::Octopus(IWorld * world, const Vector3 & position, const IBodyPtr & body)
	: EnemyBase(world, position, body)
{
	//animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));	// モデルを読み込む
}

// 初期化
void Octopus::initialize()
{
	EnemyBase::initialize();
}

// 接触判定
void Octopus::onCollide(Actor& other)
{
	if (other.isAction()) return;
	if (other.getName() == "Player" || other.getName() == "Car")
	{
		// 自分からプレーヤーへの方向ベクトル
		Vector3 direction_to_player = other.getPosition() - position_;

		other.receiveMessage(EventMessage::Hit_Enemy,(void*)&direction_to_player);

		on_Barrier(world_->findActor(other.getName()), world_->findActor("Enemy"));
	}
	if (other.getName() == "Player") {
		if(state_ != EnemyState::Escape&&state_ != EnemyState::DiscoveryStart && !is_event_)change_state(EnemyState::DiscoveryStart);
	}
}