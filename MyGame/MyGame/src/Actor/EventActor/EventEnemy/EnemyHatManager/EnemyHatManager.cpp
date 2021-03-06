#include "EnemyHatManager.h"
#include "../../../../World/IWorld.h"

#include "EnemyHat\EnemyHat.h"
EnemyHatManager::EnemyHatManager(IWorld * world, ActorPtr enemy) :
	mWorld(world),
	mEnemy(enemy)
{
	auto hat = std::make_shared<EnemyHat>(world, enemy);
	mMyHat = hat;
	mWorld->addActor(ActorGroup::ENEMY_HAT_ACTOR, hat);
}

EnemyHatManager::~EnemyHatManager()
{
}

void EnemyHatManager::SpawnHat()
{
	//現在かぶっていたら
	if (mMyHat != nullptr)return;
	//生成
	auto hat = std::make_shared<EnemyHat>(mWorld, mEnemy);
	mWorld->addActor(ActorGroup::ENEMY_HAT_ACTOR, hat);
	hat->ChangeVertex(EnemyHat::VertexItem::TAKO_HAND);
	mMyHat = hat;

}

void EnemyHatManager::DokkanHat()
{
	//かぶっていなかったら
	if (mMyHat == nullptr)return;
	//吹っ飛ばす
	static_cast<EnemyHat*>(mMyHat.get())->ChangeVertex(EnemyHat::VertexItem::HUTTOBI);
	//現在かぶっていない
	mMyHat = nullptr;
}

ActorPtr EnemyHatManager::GetHat()
{
	return mMyHat;
}
