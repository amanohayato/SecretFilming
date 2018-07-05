#pragma once
#include "../../../../Actor.h"


class EnemyHat :public Actor {
public:
	//くっつかせる頂点
	enum VertexItem
	{
		TAKO_HAND,	//手
		TAKO_HEAD,	//頭
		HUTTOBI,
		NO			//持ってない
	};
public:
	EnemyHat(IWorld* world,ActorPtr enemy);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//接触時
	virtual void onCollide(Actor& other) override;
	//持っている頂点を変える
	void ChangeVertex(const VertexItem& vertex);
	//どこに持っているかを取得
	VertexItem GetVertex();
private:
	//座標
	Vector3 mPosition;
	//回転
	Vector3 mRotate;
	Matrix mHatMat;
	//どの手にくっついてるか
	VertexItem mVertexItem;
	//エネミーのモデルハンドル
	int mEnemyModelHandle;
	//速度
	Vector3 mHatVelo;
	ActorPtr mEnemy;

	float mTime;

};