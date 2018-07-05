#include "KaiwaEventActor02.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"


KaiwaEventActor02:: KaiwaEventActor02(IWorld & world):
EventActor(world)
{

}

void KaiwaEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	

	Vector3 pos1 = Vector3(0, 400, 0);
	Vector3 pos2 = mEnemyBase->GetEventPoints().front().position_;
	pos2.y = 400;
	//UFOê∂ê¨
	auto ufo = std::make_shared<EventUfo>(mWorld, pos1, pos2);
	mWorld->addActor(ActorGroup::EVENT_ACTOR,ufo);
	mEventUfo = static_cast<EventUfo*>(ufo.get());
}

void KaiwaEventActor02::Update()
{

}

void KaiwaEventActor02::Draw() const
{
}

void KaiwaEventActor02::End()
{
	//UFOê∂ê¨

}
