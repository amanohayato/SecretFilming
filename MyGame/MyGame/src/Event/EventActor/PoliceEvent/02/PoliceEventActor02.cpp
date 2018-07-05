#include "PoliceEventActor02.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"

#include "../../../../Sound/Sound.h"
PoliceEventActor02::PoliceEventActor02(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();
	
	auto police = static_cast<Police*>(mPolice.get());
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_RUN_ANIM), true);

	//今宇宙人がいる位置
	mFirstEnemyMat = mEnemyBase->getRotation()*Matrix::CreateTranslation(mEnemyBase->getPosition());

	//エネミー移動のベクトル
	mEnemyVec = mEnemyBase->getRotation().Forward().Normalize();

	Sound::GetInstance().Play3DSE(SE_ID::POLICE_STOP_VC, (VECTOR*)&mEnemyBase->getPosition());

}

void PoliceEventActor02::Update()
{

	auto police = static_cast<Police*>(mPolice.get());
	//宇宙人は前へ移動
	mEnemyBase->getPosition() += 20.0f*mEnemyVec*Time::GetInstance().deltaTime();
	//警察官が宇宙人のいたところに移動
	mIsEnd = MoveActor::Move(police->GetMatrix(), mFirstEnemyMat);
}

void PoliceEventActor02::Draw() const
{
}

void PoliceEventActor02::End()
{
}
