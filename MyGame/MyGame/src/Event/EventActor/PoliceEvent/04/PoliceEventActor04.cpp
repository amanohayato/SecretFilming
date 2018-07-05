#include "PoliceEventActor04.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"
PoliceEventActor04::PoliceEventActor04(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor04::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Idle), false);

	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();

	auto police = static_cast<Police*>(mPolice.get());
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_POINT_ANIM), false);


	mEndMat = Matrix::Identity;
	mEndMat.Forward(-(police->GetMatrix().Translation() - mEnemyBase->getPosition()).Normalize());
	mEndMat.Right(Vector3::Cross(mEndMat.Forward(), Vector3::Up));
	mEndMat.Up(Vector3::Up);
	mEndMat.Translation(mEnemyBase->getPosition());
}

void PoliceEventActor04::Update()
{
	//‚±‚±‚É‚½‚Ô‚ñ’x‰„‚Í‚¢‚é
	mTime += Time::GetInstance().deltaTime();

	if (mTime >= 2.0f) {
		mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move), true);
		auto police = static_cast<Police*>(mPolice.get());
		//‰F’ˆl‚ªŒxŽ@Š¯‚ð–³Ž‹‚µ‚ÄU‚è‚Þ‚­
		Matrix startMat = mEnemyBase->getPose();
		//U‚è‚Þ‚«
		mIsEnd = MoveActor::Move(startMat, mEndMat);
		//Œ‹‰Ê‘ã“ü
		mEnemyBase->get_rotation() = startMat.RotationMatrix();
		mEnemyBase->getPosition() = startMat.Translation();

	}

	
}

void PoliceEventActor04::Draw() const
{
}

void PoliceEventActor04::End()
{
}
