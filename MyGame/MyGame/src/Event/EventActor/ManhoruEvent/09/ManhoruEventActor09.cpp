#include "ManhoruEventActor09.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
#include "../../../../Actor/EventActor/Ufo/EventUfo.h"

ManhoruEventActor09::ManhoruEventActor09(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor09::~ManhoruEventActor09()
{
}

void ManhoruEventActor09::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());


	mEventUfo = static_cast<EventUfo*>(mWorld->findActor("Ufo").get());
}

void ManhoruEventActor09::Update()
{
	//ufo‚É‰^‚Î‚ê‚Ä‚¢‚é
	mEnemyBase->getPosition() += mEventUfo->GetVelocity();
	if (mEventUfo->GetNumber() == 4) {
		mIsEnd = true;
	}
}

void ManhoruEventActor09::Draw() const
{
}

void ManhoruEventActor09::End()
{
}
