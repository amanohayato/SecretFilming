#pragma once

#include "../../EventActor.h"

class NekoBuilding;

class NekoEventActor01 :public EventActor {
public:
	NekoEventActor01(IWorld& world);
	~NekoEventActor01();

	//イベントの最初に一回だけ呼ばれる関数
	virtual void Start() override;
	//イベント中のアップデート
	virtual void Update() override;
	//イベントの描写
	virtual void Draw()const override;
	//イベントが終わった時に一回だけ呼ばれる関数
	virtual void End() override;
private:
	std::weak_ptr<NekoBuilding> neko_;
};