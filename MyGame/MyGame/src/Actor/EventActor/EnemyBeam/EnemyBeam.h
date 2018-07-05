#pragma once

#include "../../Actor.h"

#include "../../../Field/Building/BuildingBase.h"
//イベントの自販機を支配するアクター


class EnemyBeam :public Actor{
public:
	EnemyBeam(IWorld* world);
	virtual ~EnemyBeam() override;

	virtual void initialize() override;

	virtual void update(float deltaTime) override;

	virtual void draw()const override;

	//接触時
	virtual void onCollide(Actor& other) override;

	//ビームを撃つかどうか
	void SetIsBeam(bool flag);

private:
	bool mIsBeam;

	Matrix mBeamMat;

	float mBeamScaleY;
	float mBeamScaleXZ;

	float mAlpha;
};