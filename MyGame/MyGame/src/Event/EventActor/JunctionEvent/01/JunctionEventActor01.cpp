#include "JunctionEventActor01.h"

#include "../../../../Actor/Car/Car.h"
#include"../../../../Scene/Manager/GameDataManager.h"
#include"../../../../Field/Building/Town/Kousaten/KousatenBulding.h"

JunctionEventActor01::JunctionEventActor01(IWorld & world) :
	EventActor(world),
	mTime(0.0f)
{
}

JunctionEventActor01::~JunctionEventActor01()
{
}

void JunctionEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());

	int carmode = 6;
	if (mEnemyBase->getPosition().z > 660.0f) {
		if (mEnemyBase->getPosition().x < 1100.f) carmode = 4;
		else carmode = 5;
	}
	bool is_front = false;
	//車の生成
	auto car = std::make_shared<Car>(mWorld, "JunctionCar", MODEL_ID::MODEL_CAR_BLUE1, MODEL_ID::MODEL_CAR_BLUE2, MODEL_ID::MODEL_CAR_BLUE_LAMP, carmode, is_front);
	mWorld->addActor(ActorGroup::CAR_ACTOR, car);
	GameDataManager::getInstance().addCarList(car);//生成した車のポインタを送る

	junc_ = std::static_pointer_cast<KousatenBulding>(mEnemyBase->GetEventPoints().front().building_.lock());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move), true);

}

void JunctionEventActor01::Update()
{

	// 移動処理
	Vector3 target_position = junc_.lock()->getPosition() - mEnemyBase->getPosition();
	target_position = target_position.Normalize();
	Vector3 check_is_left_cross_vector = Vector3::Cross(mEnemyBase->get_rotation().Forward(), target_position);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(mEnemyBase->get_rotation().Up(), check_is_left_cross_vector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	mEnemyBase->get_rotation() *= Matrix::CreateFromAxisAngle(mEnemyBase->get_rotation().Up(), checkIsLeftDot * 10.0f);
	mEnemyBase->getPosition() += mEnemyBase->get_rotation().Forward() * 0.2f;

	constexpr float arriveLength = 10.0f;
	if (Vector2::Distance(Vector2{ mEnemyBase->getPosition().x,mEnemyBase->getPosition().z }, Vector2{ junc_.lock()->getPosition().x,junc_.lock()->getPosition().z }) <= arriveLength)
	{
		mIsEnd = true;
	}

}

void JunctionEventActor01::Draw() const
{
}

void JunctionEventActor01::End()
{
}
