#include "PoliceEventActor03.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"

#include "../../../../Sound/Sound.h"
PoliceEventActor03::PoliceEventActor03(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();

	auto police = static_cast<Police*>(mPolice.get());
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_IDLE_ANIM), true);


	mEndMat = Matrix::Identity;
	mEndMat.Forward((police->GetMatrix().Translation()-mEnemyBase->getPosition()).Normalize());
	mEndMat.Right(Vector3::Cross(mEndMat.Forward(), Vector3::Up));
	mEndMat.Up(Vector3::Up);
	mEndMat.Translation(mEnemyBase->getPosition());

	Sound::GetInstance().Play3DSE(SE_ID::POLICE_RUN_VC, (VECTOR*)&mEnemyBase->getPosition());
	mTextBox->add("PoliceEvent/policeman1.txt");
	mTextBox->add("PoliceEvent/policeman2.txt");
	mTextBox->Start_Text();
}

void PoliceEventActor03::Update()
{
	auto police = static_cast<Police*>(mPolice.get());
	//‰F’ˆl‚ªŒxŽ@Š¯‚Ì•û‚ðŒü‚­
	Matrix startMat = mEnemyBase->getPose();
	

	//U‚è‚Þ‚«
	mIsEnd = MoveActor::Move(startMat,mEndMat);
	//Œ‹‰Ê‘ã“ü
	mEnemyBase->get_rotation() = startMat.RotationMatrix();
	mEnemyBase->getPosition() = startMat.Translation();
}

void PoliceEventActor03::Draw() const
{
}

void PoliceEventActor03::End()
{
}
