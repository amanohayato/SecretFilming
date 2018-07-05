#include "NekoEventActor01.h"
#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
#include"../../../../Field/Building/Town/Neko/NekoBuilding.h"

NekoEventActor01::NekoEventActor01(IWorld & world):
	EventActor(world)
{
}

NekoEventActor01::~NekoEventActor01()
{
}

void NekoEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move));
	neko_ = std::static_pointer_cast<NekoBuilding>(mEnemyBase->GetEventPoints().front().building_.lock());

}

void NekoEventActor01::Update()
{
	// 移動処理
	Vector3 target_position = neko_.lock()->getPosition() - mEnemyBase->getPosition();
	target_position = target_position.Normalize();
	Vector3 check_is_left_cross_vector = Vector3::Cross(mEnemyBase->get_rotation().Forward(), target_position);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(mEnemyBase->get_rotation().Up(), check_is_left_cross_vector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	
	auto angle=Vector2::Angle(Vector2{ target_position.x,target_position.z }, Vector2{ mEnemyBase->getRotation().Forward().x,mEnemyBase->getRotation().Forward().z });
	
	if (angle > 10.0f)mEnemyBase->get_rotation() *= Matrix::CreateFromAxisAngle(mEnemyBase->get_rotation().Up(), checkIsLeftDot * 30.0f);
	constexpr float arriveLength = 30.0f;
	if(Vector3::Distance(mEnemyBase->getPosition(), neko_.lock()->getPosition()) > arriveLength)mEnemyBase->getPosition() += mEnemyBase->get_rotation().Forward() * 0.5f;
	
	if (Vector3::Distance(mEnemyBase->getPosition(), neko_.lock()->getPosition()) <= arriveLength&& angle <=10.0f)
	{
		mIsEnd = true;
	}
}

void NekoEventActor01::Draw() const
{
}

void NekoEventActor01::End()
{
}
