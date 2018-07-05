#pragma once

#include "../../Actor.h"

class Manhoru :public Actor {
public:
	Manhoru(IWorld* world, const Vector3& pos);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;
	//浮いているか
	void SetIsFly(bool isFly);
	//座標をセット
	Vector3& GetPosition();

	//ぶっ飛ばす
	void IsFlyMax();

	//戻ってくる
	void IsReturn();
private:
	//ぶっとばす
	bool mIsFlyMax;
	//浮いているか
	bool mIsFly;
	//車の上下移動の速度
	Vector3 mVelo;
	//座標
	Vector3 mPosition;



	//戻ってくるとき
	bool mIsReturn;
	float mStartY;
	float mEndY;
	float mLerpTime;

	float mSinNumber;

};