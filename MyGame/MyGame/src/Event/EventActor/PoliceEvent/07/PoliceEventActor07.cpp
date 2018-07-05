#include "PoliceEventActor07.h"

#include "../../../../Game/Time.h"

#include "../../../../Field/Building/Town/PoliceBox.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Actor/EventActor/Police/Police.h"

#include "../../../../Sound/Sound.h"
PoliceEventActor07::PoliceEventActor07(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}


void PoliceEventActor07::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	auto manhoruBil = static_cast<PoliceBox*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	mPolice = manhoruBil->GetPolice();
	auto police = static_cast<Police*>(mPolice.get());

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Memory_Delete), false);
	police->GetAnimation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)Police::PoliceAnim::POLICE_SICK_ANIM), true);

	Sound::GetInstance().Play3DSE(SE_ID::POLICE_BEAM_SE, (VECTOR*)&mEnemyBase->getPosition());
	Sound::GetInstance().Play3DSE(SE_ID::POLICE_SAKEBI_VC, (VECTOR*)&mEnemyBase->getPosition());

	//ここからスコアエリア
	mEnemyBase->setBaseScore(20);

	mTextBox->Increment_Text();
}

void PoliceEventActor07::Update()
{

	//ビームを0.
	mTime += Time::GetInstance().deltaTime();
	if (mEnemyBase->get_animation().isEnd()) {

		Sound::GetInstance().StopSE(SE_ID::POLICE_BEAM_SE);
		//終わり
		mEnemyBase->setBaseScore(0);
		mIsEnd = true;
	}
};

void PoliceEventActor07::Draw() const
{

	//頭フレーム取得
	int enemyModelHandle = mEnemyBase->get_animation().getModelHandle();
	int headFrame = MV1SearchFrame(enemyModelHandle, "HEAD");
	auto headDxMat = MV1GetFrameLocalWorldMatrix(enemyModelHandle, headFrame);
	Matrix headMat = Matrix::CreateRotationX(45)* DXConverter::GetInstance().ToMatrix(headDxMat);

	Matrix mat =
		Matrix::CreateScale(Vector3(1.0f, 0.2f, 1.0f))*
		headMat.RotationMatrix()*
		Matrix::CreateTranslation(headMat.Translation()-(headMat.Up().Normalize()*28.0f));



	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO_LIGHT, mat);
}

void PoliceEventActor07::End()
{
	//終わったら見回す
}
