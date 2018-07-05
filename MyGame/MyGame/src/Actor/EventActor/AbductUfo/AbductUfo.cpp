#include "AbductUfo.h"
#include"../../../Graphic/Model.h"
#include"../../../Math/Easing.h"
#include"../../Enemy/EnemyBase.h"
#include"../../../Sound/Sound.h"

static constexpr float ROTATE_Y = 20.0f;	//UFO‚ÌY‰ñ“]
static const Vector3 DOWN_SCALE{ 0.0f,200.0f,0.0f };
static const Vector3 DEFAULT_UP_SCALE{ 0.0f,300.0f,0.0f };
static constexpr float LIGHT_MAX{ 3.0f };
static constexpr float abductTime = 5.0f;

AbductUfo::AbductUfo(IWorld * world, const Vector3 & start, const Vector3 & goal):
	Actor(world, "AbductUfo", start+ DEFAULT_UP_SCALE),mStartPos(start+ DEFAULT_UP_SCALE),mGoalPos(goal+ DEFAULT_UP_SCALE),mState(State::start), direction_((goal-start).Normalize()*0.05f)
{
}

AbductUfo::~AbductUfo()
{
}

void AbductUfo::initialize()
{
	mState = State::start;
	func_ = [](float){};
	isStart_ = false;
	lightScale = 0.0f;
}

void AbductUfo::update(float deltaTime)
{
	func_(deltaTime);
}

void AbductUfo::draw() const
{
	if (!isStart_)return;
	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO, getPose());
	Matrix mUfoLightMat = Matrix::Identity;
	mUfoLightMat =
		Matrix::CreateScale(Vector3(lightScale, 1, lightScale))*
		Matrix::CreateTranslation( position_+ Vector3(0, -130, 0));
	if (mState==State::abduct|| mState == State::up)
		Model::GetInstance().Draw(MODEL_ID::MODEL_UFO_LIGHT, mUfoLightMat);

}

void AbductUfo::setTarget(const std::shared_ptr<Actor> & actor)
{
	target_ = actor;
}

void AbductUfo::begin()
{
	isStart_ = true;
	func_ = [&](float deltaTime){
		rotation_ *= Matrix::CreateRotationY(ROTATE_Y);

		switch (mState)
		{
		case AbductUfo::State::start:
			start(deltaTime);
			break;
		case AbductUfo::State::down:
			down(deltaTime);
			break;
		case AbductUfo::State::abduct:
			abduct(deltaTime);
			break;
		case AbductUfo::State::up:
			up(deltaTime);
			break;
		case AbductUfo::State::end:
			end(deltaTime);
			break;
		default:
			break;
		}
	};
}

void AbductUfo::start(float deltaTime)
{
	mLerpTime += deltaTime;
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

	//position_ = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);
	position_ = Easing::EaseOutCubic(mLerpTime, mStartPos, mGoalPos - mStartPos, 1.0f);
	
	if (mLerpTime >= 1.0f) {
		mStartPos = position_;
		mLerpTime = 0.f;
		mState = State::down;
	}
}

void AbductUfo::down(float deltaTime)
{
	mLerpTime += deltaTime;
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

	//position_ = Vector3::Lerp(mStartPos, mGoalPos - DOWN_SCALE, mLerpTime);
	position_ = Easing::Linear(mLerpTime, mStartPos, (mGoalPos - DOWN_SCALE) - mStartPos, 1.0f);

	if (mLerpTime >= 1.0f) {
		mStartPos = position_;
		mLerpTime = 0.f;
		mState = State::abduct;
		targetStartPos_ = target_.lock()->getPosition();
		std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"))->setBaseScore(20);
		target_.lock()->receiveMessage(EventMessage::Abduct_Cat);
	}
}

void AbductUfo::abduct(float deltaTime)
{
	if (!Sound::GetInstance().IsPlaySE(SE_ID::UFO_ABDUCTION_SE)) {
		Sound::GetInstance().Play3DSE(SE_ID::UFO_ABDUCTION_SE, (VECTOR*)&position_);
	}
	mLerpTime += deltaTime;
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, abductTime);

	lightScale = Easing::EaseOutCubic(MathHelper::Clamp(mLerpTime,0.0f,1.0f), 0.0f, LIGHT_MAX, 1.0f);

	target_.lock()->getPosition() = Easing::Linear(mLerpTime, targetStartPos_, position_ - targetStartPos_, abductTime);

	float rate = (abductTime - mLerpTime) / abductTime;
	Vector3 scale{ rate,rate ,rate };
	target_.lock()->getRotation() = target_.lock()->getRotation()*Matrix::CreateScale(scale);
	if (mLerpTime >= abductTime) {
		mLerpTime = 0.f;
		mState = State::up;
		target_.lock()->dead();

		std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"))->setBaseScore(0);
		
		Sound::GetInstance().StopSE(SE_ID::UFO_ABDUCTION_SE);

	}
}

void AbductUfo::up(float deltaTime)
{

	mLerpTime += deltaTime;
	mLerpTime = MathHelper::Clamp(mLerpTime, 0.0f, 1.0f);

	lightScale = Easing::EaseInCubic(MathHelper::Clamp(mLerpTime*5.0f, 0.0f, 1.0f), LIGHT_MAX, -LIGHT_MAX, 1.0f);

	//position_ = Vector3::Lerp(mStartPos, mGoalPos, mLerpTime);
	position_ = Easing::Linear(mLerpTime, mStartPos, mGoalPos - mStartPos, 1.0f);

	if (mLerpTime >= 1.0f) {
		mStartPos = position_;
		mLerpTime = 0.f;
		mState = State::end;
	}
}

void AbductUfo::end(float deltaTime)
{
	mLerpTime += deltaTime;
	direction_ = direction_*1.05f;

	position_ += direction_;

	if (mLerpTime >= 5.0f) {
		dead();
	}

}
