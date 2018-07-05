#include "ManhoruEventActor05.h"

#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"
#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/Manhoru/ManhoruBulding.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include <list>

ManhoruEventActor05::ManhoruEventActor05(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}

ManhoruEventActor05::~ManhoruEventActor05()
{
}

void ManhoruEventActor05::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	//イベントカー取得
	auto manhoruBil = static_cast<ManhoruBulding*>(static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get()));
	mManhoru = manhoruBil->GetManhoruActor();

	mStartMat = mEnemyBase->get_rotation()*Matrix::CreateTranslation(mEnemyBase->getPosition());

	auto enemyPos = mEnemyBase->getPosition();
	auto manhoruPos = mManhoru->getPosition();


	Matrix s;
	Vector3 vec = (manhoruPos - enemyPos).Normalize();
	s.Forward(vec);
	s.Up(Vector3::Up);
	s.Right(Vector3::Cross(vec, Vector3::Up));

	//マンホールの↑
	mEndMat = s.RotationMatrix() *Matrix::CreateTranslation(mManhoru->getPosition());


	mTime = 0.0f;
}

void ManhoruEventActor05::Update()
{
	mEnemyBase->getPosition() = mStartMat.Translation();
	mEnemyBase->get_rotation() = mStartMat.RotationMatrix();

	mTime += Time::GetInstance().deltaTime();
	if (mTime >= 1.0f) {
		mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move), true);
		//マンホールの上に行く移動
		mIsEnd = MoveActor::Move(mStartMat, mEndMat);

	}
}

void ManhoruEventActor05::Draw() const
{
}

void ManhoruEventActor05::End()
{
}
