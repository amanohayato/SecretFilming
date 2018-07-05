#pragma once
#include "../../../../Actor.h"


class EnemyHat :public Actor {
public:
	//���������钸�_
	enum VertexItem
	{
		TAKO_HAND,	//��
		TAKO_HEAD,	//��
		HUTTOBI,
		NO			//�����ĂȂ�
	};
public:
	EnemyHat(IWorld* world,ActorPtr enemy);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//�ڐG��
	virtual void onCollide(Actor& other) override;
	//�����Ă��钸�_��ς���
	void ChangeVertex(const VertexItem& vertex);
	//�ǂ��Ɏ����Ă��邩���擾
	VertexItem GetVertex();
private:
	//���W
	Vector3 mPosition;
	//��]
	Vector3 mRotate;
	Matrix mHatMat;
	//�ǂ̎�ɂ������Ă邩
	VertexItem mVertexItem;
	//�G�l�~�[�̃��f���n���h��
	int mEnemyModelHandle;
	//���x
	Vector3 mHatVelo;
	ActorPtr mEnemy;

	float mTime;

};