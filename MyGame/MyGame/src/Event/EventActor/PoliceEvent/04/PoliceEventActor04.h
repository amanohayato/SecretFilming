#pragma once

#include "../../EventActor.h"

class PoliceEventActor04 :public EventActor {
public:
	PoliceEventActor04(IWorld& world);

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;

private:
	float mTime;
	//警官
	ActorPtr mPolice;
	//エネミーが移動するベクトル
	Vector3 mEnemyVec;
	//エネミーが最初いた場所
	Matrix mFirstEnemyMat;
	//振り無た時の行列
	Matrix mEndMat;
};