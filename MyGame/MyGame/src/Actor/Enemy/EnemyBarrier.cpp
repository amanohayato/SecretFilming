#include "EnemyBarrier.h"
#include"../../Graphic/Model.h"
#include"../../Sound/Sound.h"

// エネミーのバリアクラス
// 担当：Ho Siu Ki（何兆祺）

// コンストラクタ
EnemyBarrier::EnemyBarrier(ActorPtr target, ActorPtr enemy,Vector3 position, Matrix rotation, bool isStop) :
	Actor(nullptr, "EnemyBarrier", position, rotation),isStop_(isStop)
{
	target_ = target;
	enemy_ = enemy;
	Vector3 dir = target_->getPosition() - enemy_->getPosition();
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
	position_ = enemy_->getPosition() + dir.Normalize() * 6.0f;
	//バリアSE
	Sound::GetInstance().Play3DSE(SE_ID::GUARD_SE, (VECTOR*)&position_);
}

// 初期化
void EnemyBarrier::initialize()
{
}

// 更新
void EnemyBarrier::update(float delta_time)
{
	if (timer_ <= 0.0f)
	{
		dead();
	}

	timer_ -= delta_time;
	if (isStop_)return;
	Vector3 dir = target_->getPosition() - enemy_->getPosition();
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
	position_ = enemy_->getPosition() + dir.Normalize() * 6.0f;
}

// 描画
void EnemyBarrier::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_BARRIER, Matrix(rotation_).Translation(position_));
}