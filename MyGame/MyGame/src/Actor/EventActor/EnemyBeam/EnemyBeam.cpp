#include "EnemyBeam.h"
#include "../../../Game/Time.h"

#include "../../Enemy/EnemyBase.h"

#include "../../Enemy/EnemyBase.h"
EnemyBeam::EnemyBeam(IWorld* world) :
	Actor(world, "EnemyBeam", Vector3::Zero),
	mBeamScaleY(0.0f),
	mBeamScaleXZ(0.0f),
	mIsBeam(false)
{
}

EnemyBeam::~EnemyBeam()
{
}

void EnemyBeam::initialize()
{
	mBeamMat = Matrix::Identity;
}

void EnemyBeam::update(float deltaTime)
{

	if (!mIsBeam) {
		mBeamScaleXZ -= 5.0f*Time::GetInstance().deltaTime();
		if (mBeamScaleXZ <= 0) {
			mBeamScaleY = 0.0f;
		}
	}
	else
	{
		mBeamScaleY += 500.0f*Time::GetInstance().deltaTime();
		mBeamScaleXZ = 1.0f;
	}
	mBeamScaleXZ = MathHelper::Clamp(mBeamScaleXZ, 0.0f, 1.0f);
	mBeamScaleY = MathHelper::Clamp(mBeamScaleY, 0.0f, 20000.0f);


	//頭フレームからマトリクスを取得
	auto enemyModelHandle = static_cast<EnemyBase*>(world_->findActor("Enemy").get())->get_animation().getModelHandle();
	int headFrame = MV1SearchFrame(enemyModelHandle, "HEAD");
	auto headDxMat = MV1GetFrameLocalWorldMatrix(enemyModelHandle, headFrame);
	auto headMat = DXConverter::GetInstance().ToMatrix(headDxMat);

	mBeamMat =
		Matrix::CreateScale(Vector3(mBeamScaleXZ, mBeamScaleY, mBeamScaleXZ))*
		headMat.RotationMatrix()*
		Matrix::CreateFromAxisAngle(world_->findActor("Enemy")->getPose().Left(), 90)*
		Matrix::CreateTranslation(headMat.Translation());

}

void EnemyBeam::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_ENEMY_BEARM, mBeamMat);
}

void EnemyBeam::onCollide(Actor & other)
{
}

void EnemyBeam::SetIsBeam(bool flag)
{
	mIsBeam = flag;
}
