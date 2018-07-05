#pragma once
#include"UI.h"

class IWorld;
class Action :public UI {
public:
	//コンストラクタ
	Action(IWorld* world,const Vector2& position);

	//初期化
	virtual void initialize()override;
	//更新
	virtual void update(float deltaTime)override;
	//描画
	virtual void draw() const override;
private:
	IWorld * world_;
	float amount{ 0.0f };
	bool is_Action{ false };
	float alpha{ 0.0f };
};