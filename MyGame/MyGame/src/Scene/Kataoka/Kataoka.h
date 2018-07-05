#pragma once
#include"../Scene.h"

#include "../../World/World.h"

class EventManager;

//シーンテンプレート
class Kataoka :public Scene {
public:
	Kataoka();
	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;

	float Direction(const Matrix& mat1, const Matrix& mat2);

	World mWorld;
	//イベントマネージャー
	EventManager* mEventManager;
	
	Vector2 mPos;

	Matrix mMat;
	Matrix mVMat;

	Matrix mLerpMat;
	float mLerpTime;
};