#include "ManhoruEventActor03.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"
#include "../../../../Field/Building/Town/Manhoru/ManhoruBulding.h"
#include "../../../../Actor/EventActor/Manhoru/Manhoru.h"

ManhoruEventActor03::ManhoruEventActor03(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor03::~ManhoruEventActor03()
{
}

void ManhoruEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	//イベントカー取得
	auto manhoruBil = static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mCar = manhoruBil->GetCarActor();
	mManhoru = manhoruBil->GetManhoruActor();


	auto carPos = static_cast<EventCar*>(mCar.get());
	mStartY = carPos->GetPosition().y;
	mEndY = carPos->GetPosition().y + 10.0f;

	mManhoruStartY = mManhoru->getPosition().y;
	mManhoruEndY = mManhoruStartY + 10.0f;

	static_cast<EventCar*>(mCar.get())->SetIsFly(true);
	static_cast<Manhoru*>(mManhoru.get())->SetIsFly(true);

	

	mLerpTime = 0.0f;

	//ここからスコアエリア
	mEnemyBase->setBaseScore(20);

	mTextBox->add("ManholeEvent/manhole1.txt");
	mTextBox->add("ManholeEvent/manhole2.txt");
	mTextBox->add("ManholeEvent/manhole3.txt");

	mTextBox->Start_Text();

}

void ManhoruEventActor03::Update()
{
	//車が上がる
	mLerpTime += Time::GetInstance().deltaTime();
	static_cast<EventCar*>(mCar.get())->GetPosition().y = MathHelper::Lerp(mStartY, mEndY, mLerpTime);
	mManhoru->getPosition().y = MathHelper::Lerp(mManhoruStartY, mManhoruEndY, mLerpTime);

	if (mLerpTime >= 3.0f) {
		mIsEnd = true;
	}
}

void ManhoruEventActor03::Draw() const
{
}

void ManhoruEventActor03::End()
{
}
