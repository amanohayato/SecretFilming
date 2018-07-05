#ifndef OCTOPUS_H_
#define OCTOPUS_H_

#include "EnemyBase.h"

// タコ型宇宙人クラス
// 担当：Ho Siu Ki（何兆祺）

class Octopus : public EnemyBase
{
public:
	// コンストラクタ
	Octopus(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	// 初期化
	void initialize() override;
	// 接触判定
	void onCollide(Actor& other) override;
};

#endif // !OCTOPUS_H_