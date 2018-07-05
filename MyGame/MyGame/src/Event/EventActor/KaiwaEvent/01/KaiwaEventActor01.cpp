#include "KaiwaEventActor01.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

KaiwaEventActor01::KaiwaEventActor01(IWorld & world):
EventActor(world)
{

}

void KaiwaEventActor01::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
}

void KaiwaEventActor01::Update()
{
	auto ptr = mEnemyBase->GetEventPoints().front();

	float dis = Vector3::Distance(ptr.position_, mEnemyBase->getPosition());


	DebugDraw::DebugDrawFormatString(0, 350, GetColor(255, 255, 255), std::to_string(dis));
	//近くにいるか判定
	if (ptr.building_.lock()->getEvent() == EventType::EVENT_BACKSTREET_KAIWA) {
		if (dis <= 50.0f) {
			//イベント中
			mEnemyBase->set_is_event(true);

			mIsEnd = true;
			//DebugDraw::DebugDrawLine3D(Vector3::VECTORToVector3(mEnemyBase->getPosition()), Vector3::VECTORToVector3(ptr.position_), GetColor(255, 0, 0));


			//Matrix mat =
			//	Matrix::CreateScale(1.0f)*
			//	Matrix::CreateRotationX(0.0f)*
			//	Matrix::CreateRotationY(0.0f)*
			//	Matrix::CreateRotationZ(0.0f)*
			//	Matrix::CreateTranslation(ptr.building_.lock()->getPosition() + ptr.building_.lock()->getRotation().Forward()*20.0f);

			//Matrix matPos = mEnemyBase->getRotation()*Matrix::CreateTranslation(mEnemyBase->getPosition());

			////移動が終わったら次に行く
			//mIsEnd = MoveActor::Move(matPos, mat);
			//mEnemyBase->getPosition() = matPos.Translation();
			//mEnemyBase->get_rotation() = matPos.RotationMatrix();
		}
	}

}

void KaiwaEventActor01::Draw() const
{
}

void KaiwaEventActor01::End()
{
	//UFO生成
 
}
