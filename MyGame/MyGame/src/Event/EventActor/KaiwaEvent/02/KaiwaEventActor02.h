#pragma once

#include "../../EventActor.h"

#include "../../../../Actor/EventActor/Ufo/EventUfo.h"


class EnemyBase;

class KaiwaEventActor02 :public EventActor {
public:
	KaiwaEventActor02(IWorld& world);

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	EventUfo* mEventUfo;

	float mTime;
	Matrix mUfoMat;
};