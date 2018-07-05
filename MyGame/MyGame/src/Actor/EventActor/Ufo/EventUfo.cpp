#include "EventUfo.h"
#include <memory>

#include "../../../Graphic/Model.h"

#include "../../../Game/Time.h"
#include "../../../Math/MathHelper.h"
EventUfo::EventUfo(IWorld* world, const Vector3& start, const Vector3& goal) :
	Actor(world, "Ufo", start),
	mStartPos(start),
	mGoalPos(goal),
	mIsLight(false)
{

}

EventUfo::~EventUfo()
{
}

void EventUfo::initialize()
{
	mUfoLightTime = 0.0f;

	mStateNumber = 0;

	mLerpTime = 0.0f;
	mRotateY = 0.0f;

	mPosition = mStartPos;
	mSevePosition = mPosition;

	mUfoMat =
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(0.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(mStartPos);

	mUfoLightMat = mUfoMat*Matrix::CreateTranslation(Vector3(0. - 10, 0));

}

void EventUfo::update(float deltaTime)
{
	mRotateY += 20.0f*Time::GetInstance().deltaTime();

	if (mIsLight)
		mUfoLightTime += Time::GetInstance().deltaTime();
	else
		mUfoLightTime -= Time::GetInstance().deltaTime();

	mUfoLightTime = MathHelper::Clamp(mUfoLightTime, 0.0f, 1.0f);

	//UFO�̓���
	switch (mStateNumber)
	{
	case 0:
	{
		//�ړI�n�܂ňړ�
		mLerpTime += 0.3f*Time::GetInstance().deltaTime();
		mPosition = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);

		mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

		//���̏�Ԃ�
		if (mLerpTime >= 1.0f) {
			//�~������
			mLerpTime = 0.0f;
			mStartPos = mGoalPos;
			mGoalPos.y = 80.0f;

			mStateNumber++;
		}

		break;
	}
	case 1:
	{
		//UFO���~������
		mPosition = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);
		mLerpTime += 0.3f* Time::GetInstance().deltaTime();


		if (mLerpTime >= 1.0f) {
			//�~���I���
			mLerpTime = 0.0f;
			mStateNumber++;
		}
		break;
	}
	case 2:
	{
		//Light��ON
		mIsLight = true;
		mLerpTime += Time::GetInstance().deltaTime();
		//�G�l�~�[�������グ�Ă���@(UFO���͈̂ړ������ɃG�l�~�[�����ړ�������)
		if (mLerpTime >= 3.0f) {
			mStartPos = mPosition;
			mGoalPos = mPosition + Vector3(10, 0, 0);
			mLerpTime = 0.0f;
			mStateNumber++;
		}
		break;
	}
	case 3:
	{
		//�G�l�~�[�������グ�Ĉړ����Ă�����
		mLerpTime += Time::GetInstance().deltaTime();
		mPosition = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);


		if (mLerpTime >= 2.0f) {
			//�㏸����
			mLerpTime = 0.0f;
			mStartPos = mPosition;
			mGoalPos.y = 400.0f;

			mStateNumber++;
		}

		break;

	}
	case 4:
	{
		//�G�l�~�[�����낵�Ă���r��
		mLerpTime += Time::GetInstance().deltaTime();

		//���̏�Ԃ�
		if (mLerpTime >= 2.0f) {
			mStateNumber++;
			mLerpTime = 0.0;
		}

		break;
	}
	case 5:
	{
		mLerpTime += Time::GetInstance().deltaTime();
		mPosition = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);

		mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);
		if (mLerpTime >= 1.0f) {
			//�A�鏀��
			mLerpTime = 0.0f;
			mStartPos = mPosition;
			mGoalPos.y = 400.0f;
			mStateNumber++;
		}
		break;
	}
	case 6:
	{
		mIsLight = false;
		mLerpTime += Time::GetInstance().deltaTime();
		mPosition = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);

		mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

		if (mLerpTime >= 1.0f) {
			dead();
		}

		break;
	}
	}

	mUfoMat =
		Matrix::CreateScale(Vector3::One*2.0f)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(mRotateY)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(mPosition);


	mUfoLightMat = Matrix::Identity;
	mUfoLightMat =
		Matrix::CreateScale(Vector3(MathHelper::Lerp(0.0f, 5.0f, mUfoLightTime), 1, MathHelper::Lerp(0.0f, 5.0f, mUfoLightTime)))*
		Matrix::CreateTranslation(Vector3(mUfoMat.Translation()) + Vector3(0, -130, 0));



	mVelo = mPosition - mSevePosition;
	mSevePosition = mPosition;
}

void EventUfo::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO, mUfoMat);

	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO_LIGHT, mUfoLightMat);
}

void EventUfo::onCollide(Actor & other)
{
}

Vector3 EventUfo::GetVelocity()
{
	return mVelo;
}

int & EventUfo::GetNumber()
{
	return mStateNumber;
}

void EventUfo::SetLightFlag(bool flag)
{
}
