#include "ManhoruEventActor10.h"

#include "../../../../Field/Building/Town/Manhoru/ManhoruBulding.h"
#include "../../../../Actor/EventActor/Manhoru/Manhoru.h"

#include "../../../../Game/Time.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
#include "../../../../Actor/EventActor/Ufo/EventUfo.h"

#include "../../../../World/World.h"


ManhoruEventActor10::ManhoruEventActor10(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor10::~ManhoruEventActor10()
{
}

void ManhoruEventActor10::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());


	mEventUfo = static_cast<EventUfo*>(mWorld->findActor("Ufo").get());

	mStartY = mEnemyBase->getPosition().y;
	mEndY = 10.0f;
	mLerpTime = 0.0f;

	auto manhoruBil =static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mManhoru = manhoruBil->GetManhoruActor();
	static_cast<Manhoru*>(mManhoru.get())->IsReturn();

	mTextBox->Hidden_Text();

}

void ManhoruEventActor10::Update()
{
	mLerpTime += Time::GetInstance().deltaTime();
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);
	mEnemyBase->getPosition().y = MathHelper::Lerp(mStartY, mEndY, mLerpTime);

	if (mLerpTime >= 1.0f) {
		//ここからスコアエリア
		mEnemyBase->setBaseScore(0);

		mIsEnd = true;
	}
}

void ManhoruEventActor10::Draw() const
{
}

void ManhoruEventActor10::End()
{
	auto manhoruBil = static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mWorld->getWalkMap().createEdge(0, manhoruBil->GetEdgeIndex());//エッジの生成
	mTextBox->End();

}
