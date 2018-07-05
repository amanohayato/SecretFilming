#include "KituenzyoEventActor01.h"

KituenzyoEventActor01::KituenzyoEventActor01(IWorld& world):
	EventActor(world)
{
}

KituenzyoEventActor01::~KituenzyoEventActor01()
{
}

void KituenzyoEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
}

void KituenzyoEventActor01::Update()
{
	auto ptr = mEnemyBase->GetEventPoints().front();

	float dis = Vector3::Distance(ptr.position_, mEnemyBase->getPosition());


	DebugDraw::DebugDrawFormatString(0, 350, GetColor(255, 255, 255), std::to_string(dis));
	//‹ß‚­‚É‚¢‚é‚©”»’è
	if (ptr.building_.lock()->getEvent() == EventType::EVENT_SMOKING) {
		if (dis <= 40.0f) {
			//ƒCƒxƒ“ƒg’†
			mEnemyBase->set_is_event(true);
			mIsEnd = true;
		}
	}

}

void KituenzyoEventActor01::Draw() const
{
}

void KituenzyoEventActor01::End()
{
}
