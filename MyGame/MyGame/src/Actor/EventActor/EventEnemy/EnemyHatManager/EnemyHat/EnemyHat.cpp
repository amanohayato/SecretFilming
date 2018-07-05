#include "EnemyHat.h"

#include "../../../../../Graphic/Model.h"
#include "../../../../../Graphic/AnimLoader.h"

#include "../../../../../Game/Time.h"

#include "../../../../../Input/Keyboard.h"

#include "../../../../Enemy/EnemyBase.h"

#include "../../../../../Graphic/AnimLoader.h"

//ポリゴン番号
const int PoliNum = 995;
const int FrameNum = 116;
const int FrameMeshNum = 0;
//フレームメッシュ:0番
//フレーム番号:16番
EnemyHat::EnemyHat(IWorld * world, ActorPtr enemy) :
	Actor(world, "EnemyHat", Vector3::Zero)
{
	mHatMat =
		Matrix::CreateScale(1)*
		Matrix::CreateRotationX(0)*
		Matrix::CreateRotationY(0)*
		Matrix::CreateRotationZ(0)*
		Matrix::CreateTranslation(Vector3::Zero);

	mEnemy = enemy;

}

void EnemyHat::initialize()
{

	mEnemyModelHandle = Model::GetInstance().GetHandle(MODEL_ID::MODEL_ENEMY);

	//Enemyのアニメーションしているモデルハンドルが違うので宮内君に相談する
	mEnemyModelHandle = static_cast<EnemyBase*>(mEnemy.get())->get_animation().getModelHandle();


	mHatVelo = Vector3::Zero;


	mPosition = Vector3::Zero;
	mRotate = Vector3::Zero;

	mVertexItem = VertexItem::TAKO_HEAD;

	mTime = 0.0f;
}

void EnemyHat::update(float deltaTime)
{
	auto enemy = world_->findActor("Enemy");



	switch (mVertexItem)
	{
	case EnemyHat::TAKO_HAND:
	{
		mTime += Time::GetInstance().deltaTime();
		//こっちでもうアニメーションを管理してしまう
		static_cast<EnemyBase*>(enemy.get())->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Hat), false);

		//手フレーム取得
		int headFrame = MV1SearchFrame(mEnemyModelHandle, "L_HAND");
		headFrame = 40;
		auto headMat = MV1GetFrameLocalWorldMatrix(mEnemyModelHandle, headFrame);
		mHatMat = DXConverter::GetInstance().ToMatrix(headMat);

		if (mTime >= 2.0f) {
			mTime = 0.0f;
			mVertexItem = EnemyHat::TAKO_HEAD;
		}
		break;
	}
	case EnemyHat::TAKO_HEAD:
	{
		//頭
		//頭フレーム取得
		int headFrame = MV1SearchFrame(mEnemyModelHandle, "HEAD");
		auto headMat = MV1GetFrameLocalWorldMatrix(mEnemyModelHandle, headFrame);
		mHatMat = DXConverter::GetInstance().ToMatrix(headMat);
		
		mPosition = mHatMat.Translation();
		mRotate = Matrix::Angle(mHatMat);

		break;
	}
	case EnemyHat::HUTTOBI:
	{
		mHatVelo.y = 20.0f;
		mVertexItem = EnemyHat::NO;
		break;
	}
	case EnemyHat::NO:
	{
		mHatVelo.y -= 20.0f*Time::GetInstance().deltaTime();

		mPosition += mHatVelo*Time::GetInstance().deltaTime();
		mHatMat =
			Matrix::CreateScale(Vector3(0.2f,0.2f,0.2f))*
			Matrix::CreateRotationX(mRotate.x)*
			Matrix::CreateRotationY(mRotate.y)*
			Matrix::CreateRotationZ(mRotate.z)*
			Matrix::CreateTranslation(mPosition);

		break;
	}
	}
}

void EnemyHat::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO, mHatMat);
}

void EnemyHat::onCollide(Actor & other)
{
}

void EnemyHat::ChangeVertex(const VertexItem & vertex)
{
	mVertexItem = vertex;
}

EnemyHat::VertexItem EnemyHat::GetVertex()
{
	return mVertexItem;
}
