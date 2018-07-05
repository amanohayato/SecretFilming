#include "Manhoru.h"
#include "../../../Graphic/Model.h"
#include "../../../Game/Time.h"

Manhoru::Manhoru(IWorld * world, const Vector3 & pos):
	Actor(world,"Manhoru",pos),
	mIsFlyMax(false),
	mIsFly(false),
	mSinNumber(0.0f),
	mIsReturn(false)
{
	mPosition = pos;
	mVelo = Vector3::Zero;
}

void Manhoru::initialize()
{

	mStartY = 100.0f;
	mEndY = position_.y;
	mLerpTime = 0.0f;
}

void Manhoru::update(float deltaTime)
{
	if (mIsReturn) {
		mLerpTime += Time::GetInstance().deltaTime();
		mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);
		position_.y = MathHelper::Lerp(mStartY, mEndY, mLerpTime);
		mVelo = Vector3::Zero;
		return;
	}


	mSinNumber += 200.0f*Time::GetInstance().deltaTime();

	if (mIsFly && !mIsFlyMax)
		mVelo.y += 5.0f*MathHelper::Sin(mSinNumber)*Time::GetInstance().deltaTime();

	if (mIsFlyMax)
		mVelo.y += 200.0f*Time::GetInstance().deltaTime();

}

void Manhoru::draw() const
{
	Matrix mat =
		Matrix::CreateScale(Vector3(1.0f, 1.0f, 1.0f))*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(0.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(position_ + mVelo);
	Model::GetInstance().Draw(MODEL_ID::MODEL_MANHOLE, mat);

	mat =
		Matrix::CreateScale(Vector3(1.0f, 1.0f, 1.0f))*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(0.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(mPosition+Vector3(0.0f,0.02f,0.0f));
	Model::GetInstance().Draw(MODEL_ID::MODEL_MANHOLE_ANA, mat);
}

void Manhoru::SetIsFly(bool isFly)
{
	mIsFly = isFly;
}

Vector3 & Manhoru::GetPosition()
{
	return mPosition;
}

void Manhoru::IsFlyMax()
{
	mIsFlyMax = true;
}




void Manhoru::IsReturn()
{
	mIsReturn = true;
}
