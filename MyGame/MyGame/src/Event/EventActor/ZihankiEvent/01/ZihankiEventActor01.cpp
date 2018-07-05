#include "ZihankiEventActor01.h"

#include "../../../../Actor/Enemy/EnemyBase.h"

#include "../../../../ID/EnumIDs.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"
ZihankiEventActor01::ZihankiEventActor01(IWorld & world) :
	EventActor(world)
{
}

void ZihankiEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	//‚ ‚½‚è”»’è–³Œø‰»
	mEnemyBase->GetEventPoints().front().building_.lock()->setActive(false);

	mEnemyBase->GetEventPoints().front().building_.lock()->Played();

}

void ZihankiEventActor01::Update()
{
	auto ptr = mEnemyBase->GetEventPoints().front();

	float dis = Vector3::Distance(ptr.position_, mEnemyBase->getPosition());


	Matrix mat =
		Matrix::CreateScale(1.0f)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(Matrix::Angle(ptr.building_.lock()->getRotation()).y /*+ 180.0f*/)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(ptr.building_.lock()->getPosition() + ptr.building_.lock()->getRotation().Forward()*10.0f);

	auto v = ptr.building_.lock();
	mat.Forward(-v->getPose().Forward());
	mat.Right(Vector3::Cross(v->getPose().Forward(), Vector3::Up));
	mat.Up(Vector3::Up);
	Matrix matPos = mEnemyBase->getRotation()*Matrix::CreateTranslation(mEnemyBase->getPosition());

	//ˆÚ“®‚ªI‚í‚Á‚½‚çŽŸ‚És‚­
	mIsEnd = MoveActor::Move(matPos, mat);
	mEnemyBase->getPosition() = matPos.Translation();
	mEnemyBase->get_rotation() = matPos.RotationMatrix();

	mEnemyBase->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Move), false);



	//DebugDraw::DebugDrawSphere3D(Vector3::Vector3ToVECTOR(ptr.building_.lock()->getPosition()), 40, 10, GetColor(0, 255, 255), GetColor(0, 255, 255), TRUE);
}

void ZihankiEventActor01::Draw() const
{

}

void ZihankiEventActor01::End()
{
}
