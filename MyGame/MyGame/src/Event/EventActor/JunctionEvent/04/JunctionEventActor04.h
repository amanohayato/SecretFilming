#pragma once

#include "../../EventActor.h"
#include"../../../../Actor/Car/Car.h"
class JunctionEventActor04 :public EventActor {
public:
	JunctionEventActor04(IWorld& world);

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	Car * mCar;
	int count{ 0 };
};