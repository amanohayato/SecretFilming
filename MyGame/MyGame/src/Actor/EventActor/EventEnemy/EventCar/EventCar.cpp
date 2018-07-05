#include "EventCar.h"

#include "../../../../Graphic/Model.h"
#include "../../../../Math/MathHelper.h"

#include "../../../../Game/Time.h"


EventCar::EventCar(IWorld * world, const Matrix& mat) :
	Actor(world, "EventCar", mat.Translation()),
	mIsFlyMax(false),
	mIsFly(false),
	mSinNumber(0.0f)
{
	mPosition = mat.Translation();
	mMat = mat;

	mVelo = Vector3::Zero;
}

void EventCar::initialize()
{
}
void EventCar::update(float deltaTime)
{
	mSinNumber += 200.0f*Time::GetInstance().deltaTime();

	if (mIsFly && !mIsFlyMax)
		mVelo.y += 5.0f*MathHelper::Sin(mSinNumber)*Time::GetInstance().deltaTime();

	if (mIsFlyMax)
		mVelo.y += 200.0f*Time::GetInstance().deltaTime();


	mMat =
		Matrix::CreateScale(Vector3::One)*
		mMat.RotationMatrix()*
		Matrix::CreateTranslation(mPosition + mVelo);

}

void EventCar::draw() const
{

	Model::GetInstance().Draw(MODEL_ID::MODEL_CAR_RED1, mMat);
}

void EventCar::shadowDraw() const
{
	draw();
}

void EventCar::onCollide(Actor & other)
{
}

void EventCar::SetIsFly(bool isFly)
{
	mIsFly = isFly;
}

Vector3 & EventCar::GetPosition()
{
	return mPosition;
}

void EventCar::IsFlyMax()
{
	mIsFlyMax = true;
}
