#include "ManhoruEventActor04.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/Manhoru/ManhoruBulding.h"
#include "../../../../Actor/EventActor/Manhoru/Manhoru.h"

ManhoruEventActor04::ManhoruEventActor04(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor04::~ManhoruEventActor04()
{
}

void ManhoruEventActor04::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	//イベントカー取得
	auto manhoruBil = static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mCar = manhoruBil->GetCarActor();
	mManhoru = manhoruBil->GetManhoruActor();

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::VendingMachine_Poi), false);



	mLerpTime = 0.0f;
}

void ManhoruEventActor04::Update()
{
	mLerpTime += Time::GetInstance().deltaTime();

	if (mLerpTime >= 1.7f) {
		//車を吹っ飛ばす
		static_cast<EventCar*>(mCar.get())->IsFlyMax();
		static_cast<Manhoru*>(mManhoru.get())->IsFlyMax();
		auto manhoruBil = static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
		manhoruBil->setActive(false);
	}


	if (mEnemyBase->get_animation().isEnd()) {
		//終わり
		mEnemyBase->setBaseScore(0);
		mIsEnd = true;
	}
}

void ManhoruEventActor04::Draw() const
{
}

void ManhoruEventActor04::End()
{
}
