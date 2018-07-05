#pragma once

#include "../../EventActor.h"

class KituenzyoEventActor02:public EventActor {
public:
	KituenzyoEventActor02(IWorld& world);
	~KituenzyoEventActor02();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	Matrix mStartMat;
	Matrix mEndMat;
	float mLerpTime;
};