#pragma once

#include "../../EventActor.h"

class KituenzyoEventActor01:public EventActor {
public:
	KituenzyoEventActor01(IWorld& world);
	~KituenzyoEventActor01();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;

};