#include "JunctionEventActor04.h"
#include"../../../../Actor/Car/Car.h"
#include"../../../../Sound/Sound.h"

JunctionEventActor04::JunctionEventActor04(IWorld & world) :
	EventActor(world)
{
}

void JunctionEventActor04::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mCar = static_cast<Car*>(mWorld->findActor("JunctionCar").get());
	Vector3 dir = mCar->getPosition() - mEnemyBase->getPosition();
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::LookLeft), false);
	else mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::LookRight), false);

	//クラクションSE
	Sound::GetInstance().Play3DSE(SE_ID::JUNCTION_CAR_HORN_SE, (VECTOR*)&mCar->getPosition());
	//CVSE
	Sound::GetInstance().Play3DSE(SE_ID::JUNCTION_HORN_VC_SE, (VECTOR*)&mCar->getPosition());
	//CV
	Sound::GetInstance().Play3DSE(SE_ID::ALIAN_VOICE_SE, (VECTOR*)&mEnemyBase->getPosition());

}

void JunctionEventActor04::Update()
{
	float dis = Vector3::Distance(mCar->getPosition(), mEnemyBase->getPosition());
	if (count == 30) {
		Sound::GetInstance().Play3DSE(SE_ID::JUNCTION_CAR_BREAK_SE, (VECTOR*)&mCar->getPosition());
	}
	if (dis < 50.0f) {
		mIsEnd = true;
	}
	count++;
}

void JunctionEventActor04::Draw() const
{
}

void JunctionEventActor04::End()
{
}
