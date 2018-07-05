#pragma once
#include "../../../ActorPtr.h"

class IWorld;
//帽子管理クラス
class EnemyHatManager {
public:
	EnemyHatManager(IWorld* world,ActorPtr enemy);
	~EnemyHatManager();
	//帽子を生成される
	void SpawnHat();
	//帽子を吹っ飛ばす
	void DokkanHat();
	//現在かぶっている帽子を取得
	ActorPtr GetHat();

private:
	IWorld* mWorld;
	//現在かぶっている帽子
	ActorPtr mMyHat;

	ActorPtr mEnemy;
};