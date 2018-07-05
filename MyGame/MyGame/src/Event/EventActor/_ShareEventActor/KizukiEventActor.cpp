#include "KizukiEventActor.h"

#include "../../../Actor/UIActor/NoticedLine.h"
#include"../../../Sound/Sound.h"

KizukiEventActor::KizukiEventActor(IWorld& world, EventType eventType) :
	EventActor(world),
	mEventType(eventType)
{
}

KizukiEventActor::~KizukiEventActor()
{
}

void KizukiEventActor::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	isEndFunc_ = [&] {
		//ƒCƒxƒ“ƒg’†
		mEnemyBase->set_is_event(true);
		mWorld->addActor(ActorGroup::EVENT_ACTOR, std::make_shared<NoticedLine>(mWorld->findActor("Enemy")));
		mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Aware), false);
		Sound::GetInstance().Play3DSE(SE_ID::NOTICE_SE,(VECTOR*)&mEnemyBase->getPosition());
	};
}

void KizukiEventActor::Update()
{
	auto ptr = mEnemyBase->GetEventPoints().front();

	float dis = Vector3::Distance(ptr.position_, mEnemyBase->getPosition());


	DebugDraw::DebugDrawFormatString(0, 350, GetColor(255, 255, 255), std::to_string(dis));
	//‹ß‚­‚É‚¢‚é‚©”»’è
	if (ptr.building_.lock()->getEvent() == mEventType) {
		//if (dis <= 40.0f) {
		if(mEnemyBase->isPathEnd()){

			//‚à‚µ“¦‘–’†‚È‚ç–³Ž‹
			if (mEnemyBase->get_state() == EnemyBase::EnemyState::Escape) {
				mEventIsEnd = true;
				return;
			}


			isEndFunc_();
			isEndFunc_ = [] {};
			mIsEnd = mEnemyBase->get_animation().isEnd();

		}
	}

}

void KizukiEventActor::Draw() const
{
}

void KizukiEventActor::End()
{
}
