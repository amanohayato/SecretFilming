#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class StopShineState : public IRandomEvent
{
public:
	// コンストラクタ
	StopShineState(IWorld& world);
	// 開始
	virtual void Initialize() override;
	// 更新
	virtual void Update() override;
	// 描画
	virtual void Draw() const override;
	// 終了しているか?
	virtual bool IsEnd() const override;
	// 終了
	virtual void End() override;
	// 次のランダムイベント
	virtual RandomEvent Next() const override;
};