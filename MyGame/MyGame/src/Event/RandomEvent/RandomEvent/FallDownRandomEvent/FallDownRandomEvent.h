#pragma once
#include "../RandomEventBase/IRandomEvent.h"

class FallDownRandomEvent : public IRandomEvent
{
public:
	// コンストラクタ
	FallDownRandomEvent(IWorld& world);
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
	// コピー禁止    
	FallDownRandomEvent(const FallDownRandomEvent& other) = delete;
	FallDownRandomEvent& operator = (const FallDownRandomEvent& other) = delete;

private:
	// ランダムイベントの追加 
	void Add(RandomEvent name, const IRandomEventPtr& event);
	// ランダムイベントの変更   
	void Change(RandomEvent name);

private:
	// ランダムイベント状態
	std::unordered_map<RandomEvent, IRandomEventPtr> randomEvents_;
	// 現在の状態
	IRandomEventPtr currentRandomEvent_;
	// 現在の状態（列挙型）
	RandomEvent randomEvent_;
};