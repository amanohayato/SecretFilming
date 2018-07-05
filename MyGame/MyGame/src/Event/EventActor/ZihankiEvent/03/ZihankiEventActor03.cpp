#include "ZihankiEventActor03.h"

#include "../../../../Game/Time.h"

#include "../../../../Sound/Sound.h"
ZihankiEventActor03::ZihankiEventActor03(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor03::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	mTime = 0.0f;

	//ここからスコアエリア
	mEnemyBase->setBaseScore(20);

	Sound::GetInstance().Play3DSE(SE_ID::VEBDINGMACHINE_ALIEN_VC1, (VECTOR*)&mEnemyBase->getPosition());

	mTextBox->add("Machine/machine1.txt");
	mTextBox->Start_Text();

}

void ZihankiEventActor03::Update()
{
	mTime += Time::GetInstance().deltaTime();
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY,(int)EnemyBase::EnemyAnimation::Angry), false);
	//赤く発光
	MV1SetMaterialEmiColor(mEnemyBase->get_animation().getModelHandle(),0,GetColorF(1.0f,0.0f,0.0f,1.0f));
	//アニメーション終わったら
	if (mEnemyBase->get_animation().isEnd()) {
		MV1SetMaterialEmiColor(mEnemyBase->get_animation().getModelHandle(), 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));

		//おわり
		mEnemyBase->setBaseScore(0);

		mIsEnd = true;
	}
}

void ZihankiEventActor03::Draw() const
{
}

void ZihankiEventActor03::End()
{
}
