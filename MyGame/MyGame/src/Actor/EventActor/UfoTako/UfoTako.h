#pragma once

#include "../../Actor.h"

#include "../../../Graphic/AnimationOutSide.h"

class UfoTako :public Actor {
public:
	UfoTako(IWorld* world, const Vector3& start, const Vector3& end);
	~UfoTako();
	//初期化
	virtual void initialize() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;

	AnimationOutSide& GetAnimation();

	//地上に出るかどうか
	void SetIsDown(bool isDown);

	//スタート地点を変える
	void SetStartPos(const Vector3& startPos);
private:
	//エネミー
	ActorPtr mEnemyBase;
	//タコのマトリクス
	Matrix mUfoTakoMat;
	Vector3 mPosition;

	Vector3 mStartPos;
	Vector3 mEndPos;

	bool mIsDown;	//地上に出ているか？

	float mLerpTime;

	AnimationOutSide mAnimation;
};