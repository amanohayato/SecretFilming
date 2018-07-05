#pragma once
#include "../../RandomEventBase/IRandomEvent.h"

class FallDownState : public IRandomEvent
{
public:
	// コンストラクタ
	FallDownState(IWorld& world);
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

private:
	std::function<void()> voice_Func;
	std::function<bool()> _scoreUpFunc;//スコア上昇を呼び出すための関数
};