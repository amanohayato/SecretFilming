#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"

#include "../UfoTako/UfoTako.h"


class EventUfo :public Actor {

public:
	EventUfo(IWorld* world,const Vector3& pos1,const Vector3& pos2);
	virtual ~EventUfo() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//接触時
	virtual void onCollide(Actor& other) override;

	//ufoの速度取得
	Vector3 GetVelocity();

	//状態番号を取得
	int& GetNumber();

private:
	void SetLightFlag(bool flag);


private:

	bool mIsLight;

	UfoTako* mUfoTako;


	int mStateNumber;

	Matrix mUfoMat;

	float mRotateY;	//UFOのY回転

	Vector3 mVelo;		//速度
	Vector3 mSevePosition;
	



	Vector3 mPosition;
	Vector3 mStartPos;	//スタート
	Vector3 mGoalPos;	//ゴール
	float mLerpTime;	//線形保管タイム

	Matrix mUfoLightMat;

	float mUfoLightTime;//光保管タイム


};