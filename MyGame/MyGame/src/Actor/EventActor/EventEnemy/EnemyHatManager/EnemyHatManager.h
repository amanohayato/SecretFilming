#pragma once
#include "../../../ActorPtr.h"

class IWorld;
//�X�q�Ǘ��N���X
class EnemyHatManager {
public:
	EnemyHatManager(IWorld* world,ActorPtr enemy);
	~EnemyHatManager();
	//�X�q�𐶐������
	void SpawnHat();
	//�X�q�𐁂���΂�
	void DokkanHat();
	//���݂��Ԃ��Ă���X�q���擾
	ActorPtr GetHat();

private:
	IWorld* mWorld;
	//���݂��Ԃ��Ă���X�q
	ActorPtr mMyHat;

	ActorPtr mEnemy;
};