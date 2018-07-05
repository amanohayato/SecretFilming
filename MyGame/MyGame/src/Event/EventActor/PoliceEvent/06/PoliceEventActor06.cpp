#include "PoliceEventActor06.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"
PoliceEventActor06::PoliceEventActor06(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor06::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();
	mEndMat = mEnemyBase->getPose(); 


	auto police = static_cast<Police*>(mPolice.get());
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_IDLE_ANIM), true);


	mEndMat = Matrix::Identity;
	mEndMat.Forward((police->GetMatrix().Translation() - mEnemyBase->getPosition()).Normalize());
	mEndMat.Right(Vector3::Cross(mEndMat.Forward(), Vector3::Up));
	mEndMat.Up(Vector3::Up);
	mEndMat.Translation(mEnemyBase->getPosition());
}

void PoliceEventActor06::Update()
{
	auto police = static_cast<Police*>(mPolice.get());
	//�F���l���x�@���Ƀr�[���𓖂Ă邽�߂ɐU�����
	Matrix startMat = mEnemyBase->getPose();
	//�U��ނ�
	mIsEnd = MoveActor::Move(startMat,mEndMat);
	//���ʑ��
	mEnemyBase->get_rotation() = startMat.RotationMatrix();
	mEnemyBase->getPosition() = startMat.Translation();
}

void PoliceEventActor06::Draw() const
{
}

void PoliceEventActor06::End()
{
}
