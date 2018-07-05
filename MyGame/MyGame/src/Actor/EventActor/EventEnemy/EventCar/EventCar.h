#pragma once
#include "../../../Actor.h"


class EventCar :public Actor {
public:
	EventCar(IWorld* world,const Matrix& mat);

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;
	virtual void shadowDraw()const override;

	//接触時
	virtual void onCollide(Actor& other) override;

	//浮いているか
	void SetIsFly(bool isFly);
	//座標をセット
	Vector3& GetPosition();

	//ぶっ飛ばす
	void IsFlyMax();

private:
	//ぶっとばす
	bool mIsFlyMax;
	//浮いているか
	bool mIsFly;
	//車の上下移動の速度
	Vector3 mVelo;
	//座標
	Vector3 mPosition;

	Matrix mMat;
	
	float mSinNumber;
};