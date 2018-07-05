#pragma once

#include"UI.h"

class IWorld;
class ShutterFrame {
public:
	//コンストラクタ
	ShutterFrame(IWorld* world);

	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw(Vector2& position, Vector2& size) const;
private:
	IWorld * world_;
	float amount{ 1.0f };
	float alpha{ 0.0f };
};