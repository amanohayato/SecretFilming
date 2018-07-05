#pragma once

#include"UI.h"

class IWorld;
class CameraUI{
public:
	//コンストラクタ
	CameraUI(IWorld* world);

	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw() const;
private:
	IWorld * world_;
	float alpha_ = 1.0f;
	bool alpha_up_ = false;
	static const int speed_ = 2;
};