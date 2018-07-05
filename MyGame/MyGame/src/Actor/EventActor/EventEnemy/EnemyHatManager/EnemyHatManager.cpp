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
	//Œ»İ‚©‚Ô‚Á‚Ä‚¢‚½‚ç
	if (mMyHat != nullptr)return;
	//¶¬
	auto hat = std::make_shared<EnemyHat>(mWorld, mEnemy);
	mWorld->addActor(ActorGroup::ENEMY_HAT_ACTOR, hat);
	hat->ChangeVertex(EnemyHat::VertexItem::TAKO_HAND);
	mMyHat = hat;

}

void EnemyHatManager::DokkanHat()
{
	//‚©‚Ô‚Á‚Ä‚¢‚È‚©‚Á‚½‚ç
	if (mMyHat == nullptr)return;
	//‚Á”ò‚Î‚·
	static_cast<EnemyHat*>(mMyHat.get())->ChangeVertex(EnemyHat::VertexItem::HUTTOBI);
	//Œ»İ‚©‚Ô‚Á‚Ä‚¢‚È‚¢
	mMyHat = nullptr;
}

ActorPtr EnemyHatManager::GetHat()
{
	return mMyHat;
}
