#include "UfoTako.h"
#include "../../../Game/Time.h"

#include "../../../Graphic/Model.h"

#include "../../../Graphic/AnimLoader.h"
#include "../../Enemy/EnemyBase.h"
UfoTako::UfoTako(IWorld* world, const Vector3& start, const Vector3& end) :
	Actor(world, "UfoTako", start),
	mStartPos(start),
	mEndPos(end),
	mAnimation(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ENEMY))
{
}

UfoTako::~UfoTako()
{
}

void UfoTako::initialize()
{
	mLerpTime = 0.0f;
	mIsDown = false;

	mPosition = mStartPos;

	mUfoTakoMat =
		Matrix::CreateScale(1.0f)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(0.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(mStartPos);

	mEnemyBase = world_->findActor("Enemy");
	mAnimation.changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move));
}

void UfoTako::update(float deltaTime)
{
	mAnimation.update(1.0f);
	if (mIsDown)
		mLerpTime += 0.5f* Time::GetInstance().deltaTime();
	else
		mLerpTime -= 0.5f* Time::GetInstance().deltaTime();

	mPosition = Vector3::Lerp(mStartPos, mEndPos, mLerpTime);

	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

	auto enemyPos = mEnemyBase->getPosition();
	enemyPos.y = 0.0f;
	auto takoPos = mPosition;
	takoPos.y = 0.0f;


	mUfoTakoMat = Matrix::Identity;
		//Matrix::CreateScale(Vector3::One)*
		//Matrix::CreateRotationX(0.0f)*
		//Matrix::CreateRotationY(0.0f)*
		//Matrix::CreateRotationZ(0.0f)*
		//Matrix::CreateTranslation(mPosition);



	mUfoTakoMat.Forward(enemyPos - takoPos);
	mUfoTakoMat.Up(Vector3::Up);
	mUfoTakoMat.Left(Vector3::Cross((enemyPos - takoPos).Normalize() , Vector3::Up));
	mUfoTakoMat.Translation(mPosition);



}

void UfoTako::draw() const
{
	mAnimation.Draw(mUfoTakoMat);
}

AnimationOutSide & UfoTako::GetAnimation()
{
	return mAnimation;
}


void UfoTako::SetIsDown(bool isDown)
{
	mIsDown = isDown;
}

void UfoTako::SetStartPos(const Vector3 & startPos)
{
	mStartPos = startPos;
}
